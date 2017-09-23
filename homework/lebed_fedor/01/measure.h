#pragma once

#include "config.h"
#include "timer.h"

void
fill_matrix(int m[N][N])
{
    std::srand(0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            m[i][j] = std::rand();
        }
    }
}

using SumMethod = long (*)(const int m[N][N]);

double
measure_avg_time(SumMethod sm)
{
    volatile long x;
    int (* m)[N] = new int[N][N];
    fill_matrix(m);

    for (int i = 0; i < WARMUP; i++) {
        x = sm(m);
    }

    Timer t;
    for (int i = 0; i < TESTS; i++) {
        x = sm(m);
    }
    long elapsed = t.elapsed();

    delete[] m;
    return elapsed/(double)TESTS;
}
