#ifndef FFT_H
#define FFT_H

#include <complex.h>
#include <math.h>

/**
 * perform discrete fourier transformation
 * */
void dft(const float *input, float *magnitude, int N);

#endif // !FFT_H
