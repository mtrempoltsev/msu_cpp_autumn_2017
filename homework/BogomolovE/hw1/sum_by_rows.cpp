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


int main()
{
    const int N = 10000;
    const int M = 10000;

    //create array of size NxM with accessing by [i][j]
    int *a;
    a = (int *)malloc(N*M*sizeof(int));
    using matrix = int(*)[M][N];
    matrix ptr_a = (matrix)a;

    // fill array with ones
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
           (*ptr_a)[i][j] = 1;
        }
    }

    volatile int sum = 0; //create non-optimized collecting variable
    Timer *t = new Timer; //start timer
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
           sum += (*ptr_a)[i][j];
        }
    }
    delete t; // stop timer

    //free memory
    free(a);

    return 0;
}
