#include <iostream>
#include <chrono>

#define NUMBER_OF_ATTEMPTS 7
#define MATRIX_SIZE 10000
int all_time=0;
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
        all_time+=std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};
