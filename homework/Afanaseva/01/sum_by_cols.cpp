#include <chrono>
#include <iostream>
#include <ctime>

#define SIZE_OF_MATRIX 10000
#define WARMUP_CONSTANT 100

using namespace std;

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

void init_array(int n, int* array)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            array[j * n + i] = rand() % 7;
}


int sum_by_cols(int n, int* array)
{
    volatile int sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            sum += array[j * n + i];
    return sum;
}


int main(int argc, char *argv[])
{
    const int n = SIZE_OF_MATRIX;
    const int warmup = WARMUP_CONSTANT;
    int* array = new int[n * n];

    srand(time(NULL));

    for(int i = 0; i < warmup; i++)
        init_array(n, array);

    volatile int sum = 0;
    Timer t;
    sum = sum_by_cols(n, array);

    delete[] array;
    return 0;
}
