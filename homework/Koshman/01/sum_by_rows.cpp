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
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " ms" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};


int main()
{   
    //matrix size
    const int size = 10 * 1000; 

    auto array = new int[size][size];
    volatile long int sum = 0;    

    //Initialization and warm up
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            array[i][j] = i * size + j;
        }
    }

    {
        Timer T;
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                sum += array[i][j];
            }
        }
    }
    
    delete[] array;
    return 0;
}
