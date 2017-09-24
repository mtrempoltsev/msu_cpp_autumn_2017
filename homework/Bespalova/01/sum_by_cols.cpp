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

const int max_size = 10*1000;

int main(int argc, const char * argv[])
{
    auto array = new int [max_size][max_size];
    volatile long int sum_by_rows = 0;
    
    for (int i = 0; i < max_size; i++)
        for (int j = 0; j < max_size; j++)
            array[i][j] = 1;
    
    Timer* T = new Timer();
    
    for (int j = 0; j < max_size; j++)
        for (int i = 0; i < max_size; i++)
            sum_by_rows += array[i][j];
    
    delete T;
    delete[] array;
    
    return 0;
}

