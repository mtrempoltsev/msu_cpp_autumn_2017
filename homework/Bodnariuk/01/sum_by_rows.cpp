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
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};


const int dim_size = 1200;

int main()
{
    // init section
    volatile int a[dim_size][dim_size];
    long int sum1 = 0;

    for(int i = 0; i < dim_size; ++i) {
        for(int j = 0; j < dim_size; ++j) {
            a[i][j] = 1;
        }
    }

    // warming-up
//    for (int i = 0; i < 10000000; ++i) {
//        volatile int c = i / 3;
//    }

    // first loop
    auto t1 = new Timer();
    for(int i = 0; i < dim_size; ++i) {
        for(int j = 0; j < dim_size; ++j) {
            sum1 += a[i][j];
        }
    }
    delete t1;

    return 0;
}
