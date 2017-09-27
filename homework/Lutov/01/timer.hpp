#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <ctime>
#include <cstdlib>

class Timer
{
public:
    Timer(ssize_t);
    ~Timer();

    time_t
    diff();

private:
    const std::chrono::high_resolution_clock::time_point start_;
    const ssize_t count_;
};

#endif
