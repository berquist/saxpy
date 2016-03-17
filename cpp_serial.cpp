#include <iostream>

#include "printing.h"
#include "CycleTimer.h"

void saxpy_serial(int N,
                  float scale,
                  float X[],
                  float Y[],
                  float result[])
{

  for (int i = 0; i < N; i++) {
    result[i] = (scale * X[i]) + Y[i];
  }

  return;

}

int main()
{

  const size_t N = 50 * 1000 * 1000; // 50 M element vectors
  const size_t TOTAL_BYTES = 4 * N * sizeof(float);
  const size_t TOTAL_FLOPS = 2 * N;
  const size_t num_run_times = 5;

  printf("Number of repeats: %d\n", num_run_times);

  size_t i;

  float scale = 2.f;

  float* arrayX = new float[N];
  float* arrayY = new float[N];
  float* result = new float[N];

  // initialize array values
  for (i = 0; i < N; i++)
  {
    arrayX[i] = i;
    arrayY[i] = i;
    result[i] = 0.f;
  }

  //
  // Run the serial implementation.
  //
  double minSerial = 1e30;
  for (i = 0; i < num_run_times; ++i) {
    double startTime = CycleTimer::currentSeconds();
    saxpy_serial(N, scale, arrayX, arrayY, result);
    double endTime = CycleTimer::currentSeconds();
    minSerial = std::min(minSerial, endTime - startTime);
  }

  printf("[saxpy serial]:\t\t[%.3f] ms\t[%.3f] GB/s\t[%.3f] GFLOPS\n",
         minSerial * 1000,
         toBW(TOTAL_BYTES, minSerial),
         toGFLOPS(TOTAL_FLOPS, minSerial));

  // Clear out the buffer
  for (i = 0; i < N; ++i)
    result[i] = 0.f;

  delete[] arrayX;
  delete[] arrayY;
  delete[] result;

  return 0;

}
