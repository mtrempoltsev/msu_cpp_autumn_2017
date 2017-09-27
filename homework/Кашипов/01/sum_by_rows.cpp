#include <iostream>
#include <chrono>
#include <iostream>
using namespace std;
int N=10000;
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
    int i=0;
    int j=0;
    int sum=0;
    int** matrix = new int*[N];
    for(i=0;i<N;i++)
    	matrix[i] = new int[N];
 
    if (matrix==nullptr)
    {
	cout << "Error" << endl;
	return 0;
    }

    for(i=0;i<N;i++)
	for(j=0;j<N;j++)
	{
	    matrix[i][j]=rand()%100;
	}


    {
	Timer* T = new Timer() ;
	for(i=0;i<N;i++)
	    for(j=0;j<N;j++)
	        sum+=matrix[i][j];
	cout << "Matrix sum = " << sum <<endl;
	delete T;
    }


    for(i=0;i<N;i++)
    	delete[] matrix[i];
    delete[] matrix;
    return 1;
}
