#include <iostream>
#include <chrono>
using namespace std;

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
    //Setting up a timer and beginning calculations.
    const auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numRow; ++i)
    {
        for (int j = 0; j < numCol; ++j)
        {
            sum += matrix[i][j];
        }
    }
    const auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count() << " us" << std::endl;
    //Cleaning memory
    for(int i = 0; i < numRow; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    cout << "Sum = " << sum << endl;
    return 0;
}
