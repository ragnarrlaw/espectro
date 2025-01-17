#include "decode.h"
#include <libavcodec/avcodec.h>
#include <libavcodec/packet.h>
#include <libavformat/avformat.h>
#include <libavutil/error.h>
#include <libavutil/opt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Decode audio files into PCM format
 * */

void decode_audio(const char *filename, const char *output_pcm) {
  AVFormatContext *format_ctx = NULL;
  AVCodecContext *codec_ctx = NULL;
  const AVCodec *codec = NULL;
  AVPacket packet;
  AVFrame *frame = NULL;
  FILE *pcm_file = NULL;
  int audio_stream_index = -1;
  int ret = 0;

  if (avformat_open_input(&format_ctx, filename, NULL, NULL) < 0) {
    fprintf(stderr, "failed to open input file: '%s'\n", filename);
    return;
  }

  if (avformat_find_stream_info(format_ctx, NULL) < 0) {
    fprintf(stderr, "failed to find stream information\n");
    return;
  }

  for (int i = 0; i < format_ctx->nb_streams; i++) {
    if (format_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
      audio_stream_index = i;
      break;
    }
  }

  if (audio_stream_index == -1) {
    fprintf(stderr, "failed to find audio stream\n");
    return;
  }

  codec = avcodec_find_decoder(
      format_ctx->streams[audio_stream_index]->codecpar->codec_id);
  if (!codec) {
    fprintf(stderr, "failed to find decoder\n");
    return;
  }

  codec_ctx = avcodec_alloc_context3(codec);
  if (!codec_ctx) {
    fprintf(stderr, "failed to allocate codec context\n");
    return;
  }

  if (avcodec_parameters_to_context(
          codec_ctx, format_ctx->streams[audio_stream_index]->codecpar) < 0) {
    fprintf(stderr, "failed to copy codec parameters to codec context\n");
    return;
  }

  if (avcodec_open2(codec_ctx, codec, NULL) < 0) {
    fprintf(stderr, "failed to open codec\n");
    return;
  }

  pcm_file = fopen(output_pcm, "wb");
  if (!pcm_file) {
    fprintf(stderr, "failed to open output file: '%s'\n", output_pcm);
    return;
  }

  // av_init_packet(&packet);
  packet.data = NULL;
  packet.size = 0;

  frame = av_frame_alloc();
  if (!frame) {
    fprintf(stderr, "failed to allocate frame\n");
    return;
  }

  while (av_read_frame(format_ctx, &packet) >= 0) {
    if (packet.stream_index == audio_stream_index) {
      ret = avcodec_send_packet(codec_ctx, &packet);
      if (ret < 0) {
        fprintf(stderr, "failed to send packet for decoding\n");
        break;
      }

      while (ret >= 0) {
        ret = avcodec_receive_frame(codec_ctx, frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
          break;
        } else if (ret < 0) {
          fprintf(stderr, "error during encoding\n");
          break;
        }

        fwrite(frame->data[0], 1, frame->linesize[0], pcm_file);
      }
    }
    av_packet_unref(&packet);
  }

  fclose(pcm_file);
  av_frame_free(&frame);
  avcodec_free_context(&codec_ctx);
  avformat_close_input(&format_ctx);
}
