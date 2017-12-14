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
    Timer time = Timer();
    for (int i = 0; i < ARR_SIZE; i++) {
        for (int j = 0; j < ARR_SIZE; j++)
            a[j][i] = i + j;
    }
}
