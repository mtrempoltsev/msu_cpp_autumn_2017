//
// Created by vladimir on 25.09.17.
//
#pragma once
#ifndef CPLPLTSK_1_TIMER_H
#define CPLPLTSK_1_TIMER_H


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


#endif //CPLPLTSK_1_TIMER_H
