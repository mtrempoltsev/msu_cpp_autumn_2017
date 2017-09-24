#pragma once

#include "config.h"
#include "timer.h"

// fills matrix with predefined sequence of values
void fill_matrix(int m[DIM][DIM])
{
    std::srand(0);
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            m[i][j] = std::rand();
        }
    }
}

using SumMethod = long (*)(const int m[DIM][DIM]);

// times block of tests on SumMethod and
// returns average time required for one SumMethod
double measure_avg_time(SumMethod sm)
{
    // volatile is to guarantee sm is actually called
    volatile long x;

    // matrix created & initialized
    int (* m)[DIM] = new int[DIM][DIM];
    fill_matrix(m);

    // warmpu runs
    for (int i = 0; i < WARMUP_RUNS; i++) {
        x = sm(m);
    }

    // measure runs
    Timer t;
    for (int i = 0; i < MEASURE_RUNS; i++) {
        x = sm(m);
    }
    long elapsed = t.elapsed();

    delete[] m;
    return elapsed/(double)MEASURE_RUNS;
}
