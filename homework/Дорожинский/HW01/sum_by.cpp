#include <chrono>
#include <iostream>

#define SIZE 10000

using array = int (*)[SIZE];


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

auto sum_by_rows(array arr)
{
    auto sum = 0;
    Timer t;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            sum += arr[i][j];
        }
    }
    return sum;
}

auto sum_by_cols(array arr)
{   
    auto sum = 0;
    Timer t;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            sum += arr[j][i];
        }
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    array arr = (array) malloc(SIZE * SIZE * sizeof(int));

    for (auto i = 0; i < SIZE; ++i)
    {
        for (auto j = 0; j < SIZE; ++j)
        {
            arr[i][j] = i;
        }
    }

    std::cout << "Warmup by rows: " << sum_by_rows(arr) << std::endl;
    std::cout << "By rows: " << sum_by_rows(arr) << std::endl;
    std::cout << "By cols: " << sum_by_cols(arr) << std::endl;

    free(arr);
    return 0;
}