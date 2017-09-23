#include <iostream>
#include <chrono>
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
    int* matrix = nullptr;
    int sum = 0;
    int numCol = 10000;
    int numRow = 10000;
    matrix = new int[numCol*numRow];
    for (int i = 0; i < numRow; ++i)
    {
        for (int j = 0; j < numCol; ++j)
        {
            matrix[i*numCol + j] = i - j;
        }
    }
    Timer t;
    for (int j = 0; j < numCol; ++j)
    {
        for (int i = 0; i < numRow; ++i)
        {
            sum += matrix[i*numCol + j];
        }
    }
    delete matrix;
    cout << "Sum = " << sum << endl;
    return 0;
}
