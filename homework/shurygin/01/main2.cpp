#include <chrono>
#include <iostream>

const int maxSize = 10*1000;

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
	int* m1 = new int[maxSize * maxSize];
	int* m2 = new int[maxSize * maxSize];
	int* res = new int[maxSize * maxSize];

	for(size_t i = 0; i < maxSize; ++i)
	   for(size_t j = 0; j < maxSize; ++j)
	   {
		   m1[i * maxSize + j] = i;
		   m2[i * maxSize + j] = j;
	   }

	{
		Timer t;
		for(size_t i = 0; i < maxSize; ++i)
		   for(size_t j = 0; j < maxSize; ++j)
		   {
				res[j * maxSize + i] = m1[j * maxSize + i] + m2[j * maxSize + i];
		   }
	}

	delete[] m1;
	delete[] m2;
	delete[] res;
}
