#include <chrono>
#include <iostream>

class Timer
{
public:
    Timer()
        : start_(std::chrono::high_resolution_clock::now())
    {
    }

    int time_passed()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count();
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};
