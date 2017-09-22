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
    // std::cout << "start";
    // init section
    volatile int a[dim_size][dim_size];
    long int sum2 = 0;
    // std::cout << "after mem loc";

    for(int i = 0; i < dim_size; ++i) {
        for(int j = 0; j < dim_size; ++j) {
            a[i][j] = 1;
        }
    }
    // std::cout << "after init";

    // warming-up
//    for (int i = 0; i < 10000000; ++i) {
//        volatile int c = i / 3;
//    }
    // std::cout << "after warming-up";

    // second loop
    auto t2 = new Timer();
    for(int i = 0; i < dim_size; ++i) {
        for(int j = 0; j < dim_size; ++j) {
            sum2 += a[j][i];
        }
    }
    delete t2;
    // std::cout << "after loop";

    return 0;
}
