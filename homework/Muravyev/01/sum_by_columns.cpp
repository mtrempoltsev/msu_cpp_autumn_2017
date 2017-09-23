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
	int** matrix = new int*[N];
	for(int k = 0;k < N;++k)
		matrix[k] = new int[N];
	int sum = 0;
	for(int k = 0;k < N;++k){
		for(int m = 0;m < N;++m){
			matrix[k][m] = 2;
		}
	}
	Timer t;
	for(int i = 0;i < N;++i){
		for(int j = 0;j < N;++j){
			sum += matrix[j][i];
		}
	}
	delete[] matrix;
	return 0;
}
