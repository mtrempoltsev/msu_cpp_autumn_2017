#include <chrono>
#include <iostream>

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
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << "  us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};

// N - number of row
// M - number of column
const unsigned int N = 10000;
const unsigned int M = 10000;

int main() {
  volatile int Sum = 0;  // volatile not optimize ast
  int n = 0;

  int** A = new int*[N]; // init 2d array, https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
  for (int i = 0; i < N; i++)
    A[i] = new int[M];

  // put int in array
  for (int i = 0; i < N; i++) { // rows
    for (int j = 0; j < M; j++){ // columns
      A[i][j] = i*j*j;
    }
  }

  Timer* t = new Timer(); // start Timer
  for (int i = 0; i < N; i++) { // rows
    for (int j = 0; j < M; j++){ // columns
      Sum += A[i][j];
    }
  }
  delete t; //stop timer

  //delete matrix
  for (int i = 0; i < N; i++)
  {
    delete [] A[i];
  }
  delete[] A;


  return 0;
}