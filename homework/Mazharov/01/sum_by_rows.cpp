#include <iostream>
#include <chrono>

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

//average time 242087 us
int main() {

    int sizeN = 10000;
    volatile auto sum = 0;

    //matrix init
    int* matrix = (int*) malloc(sizeN * sizeN * sizeof(int));
    for (int i = 0; i < sizeN; ++i)
        for (int j = 0; j < sizeN; ++j)
            matrix[i * sizeN + j] = rand() % 10;

    Timer t;
    for (int i = 0; i < sizeN; ++i)
        for (int j = 0; j < sizeN; j++)
            sum += matrix[i * sizeN + j];

    return 0;
}