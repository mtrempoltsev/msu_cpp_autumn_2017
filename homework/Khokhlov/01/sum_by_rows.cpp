#include <iostream>
#include <chrono>



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
	Timer t;

	long int n = 10000;
	int* a = new int[n * n];
	//int a[n][n];
	for(int i = 0; i <n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			a[i * n + j] = i + j;
			//a[i][j] = i + j; 
		}
	}
	volatile  long int  sum = 0;
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j ++)
		{
			sum += a[i * n + j];
			//sum += a[i][j];
		}
	}

	delete[] a;
	return 0;
}
