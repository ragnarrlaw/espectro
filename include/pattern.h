#ifndef PATTERN
#define PATTERN

#include <math.h>
#include <ncurses.h>

void init_colors();
void visualize(const float *magnitude, int size);
void visualize_wave_pattern(const float *magnitude, int size);
void visualize_moving_wave(const float *magnitude, int size, float phase);

#endif // !PATTERN_H
