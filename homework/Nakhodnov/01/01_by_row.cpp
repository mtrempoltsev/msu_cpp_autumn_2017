#include <iostream>
#include <chrono>
#include <iostream>
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

enum
{
    MATRIX_SIZE = 10000
};

int main()
{
    int *matrix = (int *)malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(int));
    if(matrix == nullptr){
        cerr << "Allocation Problem" << endl;
        return 0;
    }
    for(int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; ++i){
       matrix[i] = i;
    }
    Timer T;
    long long matrix_sum = 0;
    for(int i = 0; i < MATRIX_SIZE; ++i){
        for(int j = 0; j < MATRIX_SIZE; ++j){
            matrix_sum += matrix[j * MATRIX_SIZE + i];
        }
    }
    cout << "Maxtrix sum :" << matrix_sum << endl;
    free(matrix);
    return 0;    
}
