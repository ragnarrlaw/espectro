#include "read.h"
#include <stdio.h>

void read_audio_file(const char *filename, float *buffer, int size) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    fprintf(stderr, "failed to open file: '%s'\n", filename);
    return;
  }

  short temp;
  for (int i = 0; i < size && fread(&temp, sizeof(short), 1, file); i++) {
    buffer[i] = temp / 32768.0; // Normalize 16-bit PCM to [-1, 1]
  }

  fclose(file);
}