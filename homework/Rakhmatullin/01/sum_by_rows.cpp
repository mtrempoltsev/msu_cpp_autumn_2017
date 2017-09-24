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
    int** matrix = nullptr;
    long int sum = 0;
    int numCol = 10000; //Number of columns
    int numRow = 10000; // Number of rows
    matrix = (int**)malloc(numRow*sizeof(int*));
    for(int i = 0; i < numRow; ++i)
    {
        matrix[i] = (int*)malloc(numCol*sizeof(int));
    }
    // Initialization of matrix
    for (int i = 0; i < numRow; ++i)
    {
        for (int j = 0; j < numCol; ++j)
        {
            matrix[i][j] = i - j;
        }
    }
    Timer t; //Timer starts. Beginning of calculations.
    for (int i = 0; i < numRow; ++i)
    {
        for (int j = 0; j < numCol; ++j)
        {
            sum += matrix[i][j];
        }
    }
    //Cleaning memory
    for(int i = 0; i < numRow; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    cout << "Sum = " << sum << endl;
    return 0;
}
