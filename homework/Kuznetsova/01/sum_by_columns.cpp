#include <chrono>
#include <iostream>

class Timer {
 public:
  Timer() : start_(std::chrono::high_resolution_clock::now()) {}

  ~Timer() {
    const auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish -
                                                                       start_)
                     .count()
              << " us (microseconds)" << std::endl;
  }

 private:
  const std::chrono::high_resolution_clock::time_point start_;
};

int main() {
  const int DIM = 10000;

  int i = 0;
  int j = 0;
  volatile int sum = 0;

  int** matrix = new int*[DIM];
  for (i = 0; i < DIM; i++) {
    matrix[i] = new int[DIM];
  }

  for (i = 0; i < DIM; i++) {
    for (j = 0; j < DIM; j++) {
      matrix[i][j] = 1;
    }
  }

  Timer t;

  for (j = 0; j < DIM; j++) {
    for (i = 0; i < DIM; i++) {
      sum += matrix[i][j];
    }
  }

  for (i = 0; i < DIM; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;

  return 0;
}
