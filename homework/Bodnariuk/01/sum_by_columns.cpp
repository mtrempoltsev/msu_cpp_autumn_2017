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


const int dim_size = 15000;

// 23849126 us
int main()
{
    // volatile auto a = new int[dim_size][dim_size];
    volatile static int a[dim_size][dim_size];
    volatile long int sum2 = 0;

    for(int i = 0; i < dim_size; ++i) {
        for(int j = 0; j < dim_size; ++j) {
            a[i][j] = 1;
        }
    }

    auto t2 = new Timer();
    for(int i = 0; i < dim_size; ++i) {
        for(int j = 0; j < dim_size; ++j) {
            sum2 += a[j][i];
        }
    }
    delete t2;

    return 0;
}
