#include <chrono>
#include <iostream>

const int MAX_N = 1e4;

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

int main(void) {
    volatile int *A[MAX_N];
    for (int i = 0; i < MAX_N; i++) {
        A[i] = new int[MAX_N];
        for (int j = 0; j < MAX_N; j++) {
            A[i][j] = (i + j) % 9999;
        }
    }

    Timer timer;
    volatile int sum = 0; 
    for (volatile int i = 0; i < MAX_N; i++) {
        for (volatile int j = 0; j < MAX_N; j++) {
            sum += A[j][i];
        }
    }

    return 0;
}
