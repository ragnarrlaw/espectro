#include "audio.h"

// PortAudio callback function
int audio_callback(const void *inputBuffer, void *outputBuffer,
                   unsigned long framesPerBuffer,
                   const PaStreamCallbackTimeInfo *timeInfo,
                   PaStreamCallbackFlags statusFlags, void *userData) {
  AudioData *data = (AudioData *)userData;
  float *out = (float *)outputBuffer;
  unsigned int i;

  for (i = 0; i < framesPerBuffer; i++) {
    if (data->current_index < data->data_size) {
      out[i] = data->audio_data[data->current_index++];
    } else {
      out[i] = 0.0f; // silence when no data is left
    }
  }
  return data->current_index >= data->data_size ? paComplete : paContinue;
}
