#include "fft.h"
#include <complex.h>
#include <math.h>

void dft(const float *input, float *magnitude, int N) {
  float max_magnitude = 0.0;

  for (int k = 0; k < N; k++) {
    double complex Xk = 0.0 + 0.0 * I;
    for (int n = 0; n < N; n++) {
      double angle = -2.0 * M_PI * k * n / N;
      Xk += input[n] * (cos(angle) + I * sin(angle));
    }
    magnitude[k] = cabs(Xk);
    if (magnitude[k] > max_magnitude) {
      max_magnitude = magnitude[k];
    }
  }

  // normalize magnitudes to the range [0, 1]
  if (max_magnitude > 0.0) {
    for (int k = 0; k < N; k++) {
      magnitude[k] /= max_magnitude;
    }
  }
}
