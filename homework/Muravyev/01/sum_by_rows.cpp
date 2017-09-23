#include <chrono>
#include <iostream>

#define N 10000

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

int main(){
	double** matrix = new double*[N];
	for(int k = 0;k < N;++k)
		matrix[k] = new double[N];
	double sum = 0;
	Timer t;
	for(int i = 0;i < N;++i){
		for(int j = 0;j < N;++j){
			sum += matrix[i][j];
		}
	}
	delete[] matrix;
	return 0;
}