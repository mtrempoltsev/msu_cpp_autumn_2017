#include <iostream>
#include <chrono>
using namespace std;

class Timer
{
public:
  Timer()
    : start_(std::chrono::high_resolution_clock::now())
    {
    }

    ~Timer()
    {
      const auto finish = std::chrono::high_resolution_clock::now();
      std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << "us" <<std::endl;
    }

private:
  const std::chrono::high_resolution_clock::time_point start_;
};

const unsigned int N = 10000;
const unsigned int M = 10000;

int main() {
  // N - число строк;
  // M - число столбцов;
  int Sum = 0;
  Timer t;
  int* A = new int [N*M]; 


  // Попробуем произвести суммирование по столбцам, такое суммирование должно занимать больше     времени, потому что тогда процессор при выполнении программы будет считывать информацию не последовательно идя по ячейкам памяти, а прыгать из одной области памяти в другую 


  for (int j = 0; j < M; j++){ // столбцы
    for (int i = 0; i < N; i++) { // строки
      A[i*N + j] = 1;
    }
  }


  for (int j = 0; j < M; j++){ // столбцы
    for (int i = 0; i < N; i++) { // строки
      Sum += A[i*N + j];
    }
  }
  
  delete A;
  return Sum;
}
