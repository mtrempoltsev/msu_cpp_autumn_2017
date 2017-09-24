#include <chrono>
#include <iostream> 

#define N 10000

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

int summ_by_columns(int** a);

int summ_by_columns(int** a){

	int Summ=0;

	for (int i=0; i<N; ++i){
		for (int j=0;j<N;++j)
			Summ+=a[j][i];	
	}

	return Summ;

}

int main(){

	Timer t;
	volatile int Summ=0;

	int** mass = new int* [N];

	for (int i=0;i<N;++i)
		mass[i]=new int[N];
	
	for (int i=0;i<N;++i){
		for (int j=0;j<N;j++)
			mass[i][j]=1;
	}

	Summ=summ_by_columns(mass);

	for (int i=0;i<N;++i)
		delete[] mass[i];

	delete mass;
	
}
