#ifndef AUDIO_H
#define AUDIO_H

#include "fft.h"
#include "pattern.h"
#include <math.h>
#include <ncurses.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512

typedef struct {
  float *audio_data;
  int data_size;
  int current_index;
} AudioData;

// PortAudio callback function
int audio_callback(const void *inputBuffer, void *outputBuffer,
                   unsigned long framesPerBuffer,
                   const PaStreamCallbackTimeInfo *timeInfo,
                   PaStreamCallbackFlags statusFlags, void *userData);

#endif // !AUDIO_H