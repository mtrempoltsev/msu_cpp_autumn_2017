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
    Timer t;
    int *a;
    a = (int *)malloc(N*M*sizeof(int));
    int *b;
    b = (int *)malloc(N*M*sizeof(int));
    int *c;
    c = (int *)malloc(N*M*sizeof(int));

    using matrix = int(*)[M][N];
    matrix ptr_a = (matrix)a;
    matrix ptr_b = (matrix)b;
    matrix ptr_c = (matrix)c;

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
           (*ptr_c)[i][j] = (*ptr_a)[i][j] + (*ptr_b)[i][j];
        }
    }

    return 0;
}
