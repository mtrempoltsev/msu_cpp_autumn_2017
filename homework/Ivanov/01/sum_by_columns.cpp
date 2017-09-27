#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;

const int SIZE = 10000;

class Timer
{
public:
    Timer()
        : start_(std::chrono::high_resolution_clock::now())
    {
    }

    ~Timer()
    {
        /*fstream fout("sum_by_columns_results", ios_base::app);
        const auto finish = std::chrono::high_resolution_clock::now();
        fout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;*/
        const auto finish = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};

int main(int argc, char const *argv[])
{
    int **arr;
    arr = new int*[SIZE];
    volatile int sum = 0;
    for(int i = 0; i < SIZE; i++) {
        arr[i] = new int[SIZE];
        for(int j = 0; j < SIZE; j++) {
            arr[i][j] = ++sum;
        }
    }
    Timer timer;
    sum = 0;
    for(volatile int j = 0; j < SIZE; j++) {
        for(volatile int i = 0; i < SIZE; i++) {
            sum += arr[i][j];
        }
    }
    return 0;
}
