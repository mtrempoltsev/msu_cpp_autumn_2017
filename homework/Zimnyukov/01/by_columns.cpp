#include <iostream>
#include "timer.h"
#include <cstdlib>
#include <stdio.h>
using namespace std;

const int N = 10000;
const int TESTS_CNT = 100;
void fill_arr(int **a)
{
    srand(time(nullptr));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            a[i][j] = rand();
}

long long sum(int **a)
{
    long long ans = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            ans += a[j][i];
    return ans;
}

int main()
{
    int **a = (int**)malloc((N * sizeof(int*)) + (N * (N * sizeof(int))));
    int *buf;
    buf = (int*)(a + N);
    for (int i = 0; i < N; i++) {
        a[i] = buf + i * N;
    } //array created
    //скопировано у вас, но полностью понято
    volatile long long s = 0;
    for (int i = 0; i < 10; ++i)
        s = sum(a); //WARMUP
    
    fill_arr(a);
    int entire = 0;
    Timer t;
    for (int i = 0; i < TESTS_CNT; ++i)
    {
        s = sum(a);
    }   //TESTING

    entire = t.time_passed();   //time_passed - текущее значение таймера    
    int average = entire / TESTS_CNT;
    printf("%d\n", average);

    free(a);
    return 0;
}
