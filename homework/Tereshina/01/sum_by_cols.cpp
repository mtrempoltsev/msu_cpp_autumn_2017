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

    int **array = new int*[N]; // memory allocation for array

    for (int i = 0; i < N; i++) {
        array[i] = new int[N]; // memory allocation for rows of array
        for (int j = 0; j < N; j++) {
            array[i][j] = 1; // fills array with 1's
        }
    }
    
    Timer *t = new Timer(); // starts timer

    volatile int sum = 0;
    
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            sum += array[i][j];
        }
    }

    delete t; // stops timer

    for (int i = 0; i < N; i++) {
        delete[] array[i]; // frees rows of array
    }

    delete[] array; //frees array

    return 0;
}
