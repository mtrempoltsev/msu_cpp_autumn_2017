#include <chrono>
#include <iostream>
#include "Timer.h"
#define N 10000


void by_columns()
{
    volatile long long int res = 0;
    int** a;
    a = (int**) malloc(N * sizeof(int*));//Memory allocation
    for(int i = 0; i < N; i++){
        a[i] = (int*) malloc(N * sizeof(int));
    }

    for(int i = 0; i < N; i++)//Filling array
    {
        for(int j = 0; j < N; j++)
        {
            a[i][j] = i + j;
        }
    }
    Timer* t = new Timer();
    for(int j = 0; j < N; j++)//Calculating sum
    {
        for(int i = 0; i < N; i++)
        {
            res += a[i][j];
        }
    }
    delete t;
    for(int i = 0; i < N; i++){//Memory deallocation
        free(a[i]);
    }
    free (a);
}
