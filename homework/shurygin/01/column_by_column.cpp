#include <chrono>
#include <iostream>

/*
   This program count avg pre-summing column by column 
*/

const int maxSize = 10*1000;

class Timer // class, which count time behind creating object and destroy
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
	int** m = new int*[maxSize];
	for(size_t i = 0; i < maxSize; ++i)
		m[i] = new int[maxSize];


	for(size_t i = 0; i < maxSize; ++i) // init array
	   for(size_t j = 0; j < maxSize; ++j)
	   {
		   m[i][j] = i;
	   }

	int sum = 0;
	{
		Timer t; //time start
		for(size_t i = 0; i < maxSize; ++i)
		   for(size_t j = 0; j < maxSize; ++j)
		   {
				sum += m[j][i]; // count column by clumn
		   }
		//time finish
	}
	

	std::cout << "Avg of matrix = " << 1.0 * sum / (maxSize * maxSize) << std::endl;

	for(size_t i = 0; i < maxSize; ++i)
		delete[] m[i];
	delete[] m;
}
