#include <iostream>
#include <limits>
#include <chrono>
#include <iostream>

#define N 10000 //количество элементов



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
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};

/*
 * В этой программе производится суммирование по строкам и замер времени работы.
 * */
int main() {

    int** arr_mat = new int* [N];

    for(size_t  i = 0; i< N; ++i)
    {
        arr_mat[i] = new int[N];
        for(size_t j =0; j<N; ++j)
            arr_mat[i][j] = i + j;
    }

    // разогрев
    std::cout<< "Разогрев: "<<std::endl;
    volatile long  sum = 0;
    for(volatile int j = 0; j < N; ++j) {
        for (volatile int i = 0; i < N; ++i) {
            sum += arr_mat[i][j];
        }
    }
   
    std::cout<<"Результат: " << sum << std::endl;
    sum = 0 ; 
    std::cout<< "Суммирование по строкам: "<<std::endl;
    // по  строкам  а потом по столбцам

    
    for(int mIt = 1; mIt <= 100; ++mIt)
    {
      Timer* timer = new Timer();
      for(volatile int i = 0; i < N; ++i) {
          for (volatile int j = 0; j < N; ++j) {
              sum += arr_mat[i][j];
          }
      }

     // std::cout<<"Итерация: "<<mIt<<std::endl;
     // std::cout<<"Результат: " << sum << std::endl;
     // std::cout<<"Время:";
      delete timer;
    }

    return 0;
}
