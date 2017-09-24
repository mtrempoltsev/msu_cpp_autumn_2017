#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>
#include <iostream>


class Timer{
public:
    Timer(): start_(std::chrono::high_resolution_clock::now()){}

    ~Timer(){
        const auto finish = std::chrono::high_resolution_clock::now();
        run_time += std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
public:
    static std::chrono::microseconds::rep run_time;
    const static std::size_t heat       = 10;
    const static std::size_t main_loop  = 20;
};

std::chrono::microseconds::rep Timer::run_time = 0;

#endif // TIMER_H_