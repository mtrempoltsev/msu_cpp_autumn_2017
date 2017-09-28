#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <ctime>
#include <cstdlib>

class Timer
{
public:
    Timer(size_t);
    ~Timer();

    time_t
    diff();

private:
    const std::chrono::high_resolution_clock::time_point start_;
    const size_t count_;
};

#endif
