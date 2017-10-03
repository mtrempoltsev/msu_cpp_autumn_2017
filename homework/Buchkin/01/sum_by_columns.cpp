#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

const uint32_t SIZE = 1e4;

uint32_t **
allocMemory()
{
	uint32_t ** mtrx = new uint32_t * [SIZE];
	for (uint32_t i = 0; i != SIZE; ++i) {
		mtrx[i] = new uint32_t [SIZE];
	}
	return mtrx;
}

void
fillMatrix(uint32_t ** mtrx)
{
	srand((unsigned int)time(nullptr));
	for (uint32_t i = 0; i != SIZE; ++i) {
		for (uint32_t j = 0; j != SIZE; ++j) {
			mtrx[i][j] = (uint32_t)rand() % 10;
		}
	}
}

void
freeMatrix(uint32_t ** mtrx)
{
	for (uint32_t i = 0; i != SIZE; ++i) {
		delete [] mtrx[i];
	}
	delete [] mtrx;
}

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

int
main()
{
	uint32_t ** a = allocMemory();
	fillMatrix(a);
	uint64_t sum = 0;
	
	{
		Timer t;
		
		for (uint32_t i = 0; i != SIZE; ++i) {
			for (uint32_t j = 0; j != SIZE; ++j) {
				sum += a[j][i];
			}
		}
	}
	
	freeMatrix(a);
	
	return 0;
}




