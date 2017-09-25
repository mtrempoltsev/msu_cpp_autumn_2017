#include <chrono>
#include <iostream>
#include "Timer.h"
#define N 10000

/*class Timer
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
};*/

void by_rows()
{
    volatile long long int res = 0;
    int* a = (int*) malloc(N * N * sizeof(int));
    
    //array a;

    for(int i = 0;i<N;i++)
    {
        for(int j = 0; j < N; j++)
        {
            a[i * N + j] = i + j;
        }
    }
    Timer* t = new Timer();
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            res += a[i * N + j];
        }
    }
    //std::cout << res << std::endl;
    delete t;
    /*res = 0;
    t = new Timer();
    for (int i = 0; i<N; i++)
    {
        for (int j = 0; j<N; j++)
        {
            res += a[j*N + i];
        }
    }
    delete t;
    std::cout << res << std::endl;*/
    free (a);
    //return 0;
}