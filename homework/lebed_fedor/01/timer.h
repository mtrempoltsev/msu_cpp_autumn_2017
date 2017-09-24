#pragma once

#include <chrono>
#include <iostream>

// Is used to measure time 
class Timer
{
public:
    Timer()
        : start_(std::chrono::high_resolution_clock::now())
    {
    }

    // returns time in [us] since instantiation
    int elapsed()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count();
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};
