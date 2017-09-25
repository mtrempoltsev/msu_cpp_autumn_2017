#define N 10000

#include <chrono>
#include <iostream>

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

int main() {

    int **array = new int*[N];
    for (int i = 0; i < N; i++) {
        array[i] = new int[N];
        for (int j = 0; j < N; j++) {
            array[i][j] = 1;
        }
    }
    
    Timer *t = new Timer();

    volatile int sum = 0;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += array[i][j];
        }
    }

    delete t;

 //   std::cout << sum << std::endl;

    delete[] array;
}
