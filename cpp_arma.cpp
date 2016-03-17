#include <iostream>
#include <armadillo>

#include "printing.h"
#include "CycleTimer.h"

void saxpy_arma_copy(float scale,
                     arma::Col<float> X,
                     arma::Col<float> Y,
                     arma::Col<float>& result)
{

  result = (scale * X) + Y;

  return;

}

void saxpy_arma_reference(float scale,
                          arma::Col<float>& X,
                          arma::Col<float>& Y,
                          arma::Col<float>& result)
{

  result = (scale * X) + Y;

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

  arma::Col<float> arrayX(N);
  arma::Col<float> arrayY(N);
  arma::Col<float> result(N);

  // initialize array values
  for (i = 0; i < N; i++) {
    arrayX(i) = i;
    arrayY(i) = i;
    result(i) = 0.f;
  }

  //
  // Run the serial Armadillo implementation, call by value.
  //
  double min_arma_serial_cbv = 1e30;
  for (i = 0; i < num_run_times; ++i) {
    double startTime = CycleTimer::currentSeconds();
    saxpy_arma_copy(scale, arrayX, arrayY, result);
    double endTime = CycleTimer::currentSeconds();
    min_arma_serial_cbv = std::min(min_arma_serial_cbv, endTime - startTime);
  }

  printf("[saxpy arma serial cbv]:\t\t[%.3f] ms\t[%.3f] GB/s\t[%.3f] GFLOPS\n",
         min_arma_serial_cbv * 1000,
         toBW(TOTAL_BYTES, min_arma_serial_cbv),
         toGFLOPS(TOTAL_FLOPS, min_arma_serial_cbv));

  // Clear out the buffer
  for (i = 0; i < N; i++)
    result(i) = 0.f;

  //
  // Run the serial Armadillo implementation, call by reference.
  //
  double min_arma_serial_cbr = 1e30;
  for (i = 0; i < num_run_times; ++i) {
    double startTime = CycleTimer::currentSeconds();
    saxpy_arma_reference(scale, arrayX, arrayY, result);
    double endTime = CycleTimer::currentSeconds();
    min_arma_serial_cbr = std::min(min_arma_serial_cbr, endTime - startTime);
  }

  printf("[saxpy arma serial cbr]:\t\t[%.3f] ms\t[%.3f] GB/s\t[%.3f] GFLOPS\n",
         min_arma_serial_cbr * 1000,
         toBW(TOTAL_BYTES, min_arma_serial_cbr),
         toGFLOPS(TOTAL_FLOPS, min_arma_serial_cbr));

  // Clear out the buffer
  for (i = 0; i < N; i++)
    result(i) = 0.f;

  return 0;

}
