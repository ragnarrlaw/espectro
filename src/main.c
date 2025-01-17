#include "audio.h"
#include "fft.h"
#include "pattern.h"
#include "read.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define SAMPLE_SIZE 512

int main() {

  float audio_data[SAMPLE_SIZE];
  float magnitude[SAMPLE_SIZE];

#ifdef MOVING_WAVES
  initscr();
  noecho();
  curs_set(FALSE);
  init_colors();

  float phase = 0.0;
  while (1) {
    read_audio_file("test/audio/audio.pcm", audio_data, SAMPLE_SIZE);
    dft(audio_data, magnitude, SAMPLE_SIZE);
    visualize_moving_wave(magnitude, SAMPLE_SIZE, phase);
    phase += 1;
    napms(50);
  }
  endwin();
#endif

#ifdef VISUALIZE
  initscr();
  noecho();
  curs_set(FALSE);
  init_colors();

  while (1) {
    read_audio_file("test/audio/audio.pcm", audio_data, SAMPLE_SIZE);
    dft(audio_data, magnitude, SAMPLE_SIZE);
    visualize(magnitude, SAMPLE_SIZE);
    napms(50);
  }
  endwin();
#endif

#ifdef WAVE_PATTERN_AUDIO
  float phase = 0.0;

  AudioData audio_data_struct;
  audio_data_struct.audio_data = malloc(SAMPLE_SIZE * sizeof(float));
  audio_data_struct.data_size = SAMPLE_SIZE;
  audio_data_struct.current_index = 0;

  read_audio_file("test/audio/audio.pcm", audio_data_struct.audio_data,
                  SAMPLE_SIZE);

  PaError err;
  if ((err = Pa_Initialize()) != paNoError) {
    fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
    return EXIT_FAILURE;
  }

  PaStream *stream;
  if ((err = Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE,
                                  FRAMES_PER_BUFFER, audio_callback,
                                  &audio_data_struct)) != paNoError) {
    fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
    return EXIT_FAILURE;
  }

  if ((err = Pa_StartStream(stream)) != paNoError) {
    fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
    return EXIT_FAILURE;
  }

  initscr();
  noecho();
  curs_set(FALSE);
  init_colors();

  // visualization loop
  while (Pa_IsStreamActive(stream) == 1) {
    memcpy(audio_data,
           audio_data_struct.audio_data + audio_data_struct.current_index,
           SAMPLE_SIZE * sizeof(float));
    dft(audio_data, magnitude, SAMPLE_SIZE);
    visualize_moving_wave(magnitude, SAMPLE_SIZE, phase);
    phase += 0.1;
    napms(50); // wait to sync visualization
  }

  free(audio_data_struct.audio_data);
  endwin();

  if ((err = Pa_StopStream(stream)) != paNoError) {
    fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
  }
  Pa_CloseStream(stream);
  Pa_Terminate();
#endif

  return EXIT_SUCCESS;
}
