#include "timer.hpp"

#include <iostream>

Timer::Timer(ssize_t count)
        : start_(std::chrono::high_resolution_clock::now()),
          count_(count)
{
}

Timer::~Timer()
{
    const auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() / count_ << " us" << std::endl;
}

time_t
Timer::diff()
{
    const auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() / count_;
}
