#include <iostream>
#include <chrono>

#define N 10000

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

int main()
{
    volatile int** arr = new volatile int* [N];

    for(int i = 0; i < N; i++)
    {
        arr[i] = new volatile int [N];
        for(int j = 0; j < N; j++)
        {
            arr[i][j] = rand() % 1000 - 500;
        }
    }

    long long sum = 0;

    for(int run = 0; run < 20; run++) {
        Timer t;
        for(int j = 0; j < N; j++) {
            for(int i = 0; i < N; i++) {
                sum += arr[i][j];
            }
        }
    }

    return 0;
}
