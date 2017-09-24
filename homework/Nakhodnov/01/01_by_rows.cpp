#include <iostream>
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
using namespace std;

enum
{
    MATRIX_SIZE = 10000
};

using array = int (*)[MATRIX_SIZE];


int main()
{
    array matrix = (array)(new int[MATRIX_SIZE * MATRIX_SIZE]);
    if(matrix == nullptr){
       cerr << "Allocation Problem" << endl;
       return 0;
    }
    for(int i = 0; i < MATRIX_SIZE; ++i){
        for(int j = 0; j < MATRIX_SIZE; ++j){
            matrix[i][j] = i + j;
        }
    }
    Timer T;
    long long matrix_sum = 0;
    for(int i = 0; i < MATRIX_SIZE; ++i){
        for(int j = 0; j < MATRIX_SIZE; ++j){
            matrix_sum += matrix[i][j];
        }
    }
    cout << "Maxtrix sum :" << matrix_sum << endl;
    delete[] matrix;
    return 0;    
}
