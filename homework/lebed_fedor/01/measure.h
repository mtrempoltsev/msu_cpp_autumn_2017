#pragma once

#include "config.h"
#include "timer.h"

int *
create_matrix(int n)
{
    int *m = new int[n*n];
    std::srand(0);
    for (int i = 0; i < n*n; i++) {
        m[i] = std::rand();
    }
    return m;
}

typedef long (* SumMethod)(int n, const int *m);

double
measure(SumMethod sm)
{
    volatile long x;
    int *m = create_matrix(MATRIX_ORDER);

    for (int i = 0; i < WARMUP; i++) {
        x = sm(MATRIX_ORDER, m);
    }

    Timer t;
    for (int i = 0; i < TESTS; i++) {
        x = sm(MATRIX_ORDER, m);
    }
    long elapsed = t.elapsed();

    delete[] m;
    return elapsed/(double)TESTS;
}
