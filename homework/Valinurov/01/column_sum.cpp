#include <ctime>
#include "Matrix.hpp"
#include "Timer.hpp"

const int32_t Size = 10000;
const int attempts_number = 5;

int main(){
	srand(time(NULL));

	Matrix matr(Size);

	for (int k = 0; k < attempts_number; k++)
	{
		volatile int64_t sum = 0;
		matr.Randomize();
		Timer T;

		for (int32_t i = 0; i < Size; i++)
			for (int32_t j = 0; j < Size; j++)
				sum += matr.mas[j][i];
	}

	Timer::print_average_time(attempts_number);

    return 0;
}
