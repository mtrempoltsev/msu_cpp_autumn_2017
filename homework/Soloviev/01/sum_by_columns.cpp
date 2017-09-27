#include <chrono>
#include <iostream>

//Amount of elements in the matrix
const int N = 10000;

//Amount of iterations
const int LOOPS = 100;

//Total time of execution
int totalTime = 0;

class Timer{

public:
    Timer()
        : start_(std::chrono::high_resolution_clock::now())
    {
    }

    ~Timer()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
        totalTime += std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count();
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};

int main(){
    //The matrix that will be summed
    int** matrix = new int*[N];

    for(int i = 0; i < N; i++)
        matrix[i] = new int[N];

    //Var containing the sum, made volatile so that compiler won't optimise it
    volatile int sum = 0;

    //Initialzation of the matrix
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            matrix[i][j] = i % 10;

    //First run to warm up processor
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            sum += matrix[j][i];

    //Main process
    for(int k = 0; k < LOOPS; k++){
        sum = 0;

        Timer t;

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                sum += matrix[j][i];
    }

    std::cout << (double)totalTime/LOOPS << std::endl;

    //Freeing up memory
    for(int i = 0; i < N; i++)
            delete [] matrix[i];

    delete[] matrix;
}
