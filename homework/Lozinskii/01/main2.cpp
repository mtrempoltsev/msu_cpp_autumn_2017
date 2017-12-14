#include <chrono>
#include <iostream>
#include "timer.hpp"
enum 
{
    ARR_SIZE = 10000
};

int a[ARR_SIZE][ARR_SIZE];

int
main()
{
    for (int i = 0; i < ARR_SIZE; i++) {
        for (int j = 0; j < ARR_SIZE; j++)
            a[i][j] = i + j;
    }

    Timer time = Timer();

    unsigned sum = 0;
    for (int i = 0; i < ARR_SIZE; i++) {
        for (int j = 0; j < ARR_SIZE; j++)
            sum += a[j][i];
    }
    std::cout<<sum<<std::endl;
}
