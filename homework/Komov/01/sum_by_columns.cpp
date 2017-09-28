#include <chrono>
#include <iostream>
#include <cstdlib>

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

const size_t N_RAW = 10000;
const size_t N_COL = 10000;

int main(int argc, const char* argv[])
{
    srand(time(NULL));

    auto matrix = new int [N_RAW][N_COL];
    volatile size_t sum = 0;

    for (size_t i = 0; i < N_RAW; i++)
        for (size_t j = 0; j < N_COL; j++)
            matrix[i][j] = rand() % 10;

    Timer* T = new Timer();

    for (size_t j = 0; j < N_COL; j++)
        for (size_t i = 0; i < N_RAW; i++)
            sum += matrix[i][j];

    delete T;
    delete [] matrix;

    return 0;
}

