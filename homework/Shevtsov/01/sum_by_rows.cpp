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
  volatile int Sum = 0; // не даю компилятору оптимизировать
  int n = 0;

  int** A = new int*[N]; // инициализация двумерного массива
  for (int i = 0; i < N; i++)
    A[i] = new int[M];

  // заполнение массива
  for (int i = 0; i < N; i++) { // строки
    for (int j = 0; j < M; j++){ // столбцы
      A[i][j] = 1;
    }
  }

  Timer t; // Запускаю непосредственно перед выполнением алгоритма, чтобы не считалось лишнее время
  for (int i = 0; i < N; i++) { // строки
    for (int j = 0; j < M; j++){ // столбцы
      Sum += A[i][j];
    }
  }


  // удаление двумерного массива в прядке - обратном инициализации
  for (int i = 0; i < N; i++)
  {
    delete [] A[i];
  }
  delete[] A;


  return 0;
}
