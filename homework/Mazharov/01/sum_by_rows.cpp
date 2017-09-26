#include <iostream>
#include <chrono>

class Timer
{
private:
    const std::chrono::high_resolution_clock::time_point start_;

public:
    Timer()
            : start_(std::chrono::high_resolution_clock::now())
    {
    }

    void print_time()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }
};

//average time 200813 us
int main() {

    const auto sizeN = 10000;
    volatile auto sum = 0;

    //matrix init
    auto matrix = new int [sizeN][sizeN];
    for (int i = 0; i < sizeN; ++i)
        for (int j = 0; j < sizeN; ++j)
            matrix[i][j] = rand() % 10;

    //calculate the sum and measure the time
    Timer t;
    for (int i = 0; i < sizeN; ++i)
        for (int j = 0; j < sizeN; j++)
            sum += matrix[i][j];
    t.print_time();

    delete [] matrix;

    return 0;
}