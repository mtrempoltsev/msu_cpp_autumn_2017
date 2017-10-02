#include <iostream>
#include <chrono>

using namespace std;

//задаем размер матрицы
const int SIZE = 10000;

//класс для замера времени работы программы
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
         std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
      }

   private:
      const std::chrono::high_resolution_clock::time_point start_;
};

int main()
{
   int** matrix;
   volatile int sum = 0;

   //создаем и заполняем матрицу
   matrix = new int* [SIZE];
   for(int i = 0; i < SIZE; i++)
      matrix[i] = new int [SIZE];

   for(int i = 0; i < SIZE; i++)
      for(int j = 0; j < SIZE; j++)
         matrix[i][j] = (i+j)/SIZE;

   //запускаем таймер
   Timer *t = new Timer;

   for(int i = 0; i < SIZE; i++)
      for(int j = 0; j < SIZE; j++)
         sum += matrix[i][j];

   //останавливаем таймер
   delete t;

   for(int i = 0; i < SIZE; i++)
      delete[] matrix[i];

   delete[] matrix;

   return 0;
}

