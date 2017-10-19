#include "Matrix.h"
#include <time.h>

//========================================================================

#define ERROR_CODE 1
#define COUNT_TESTS 10

#define MAX_DIM 100
#define MAX_RAND 10000
#define COUNT_IN_SUM 10

#define RANDOM_DOUBLE ((double) (rand()%MAX_RAND))

std::vector<double> RandomVector(size_t size)
{
	std::vector<double> result(size, 0);
	for (size_t i = 0; i < size; i++)
	{
		result[i] = RANDOM_DOUBLE*RANDOM_DOUBLE / RANDOM_DOUBLE;
	}

	return result;
}

bool ProcessTestMult()
{
	size_t rows = rand() % MAX_DIM;
	size_t columns = rand() % MAX_DIM;

	std::vector<double> matrix_values = RandomVector(rows*columns);
	std::vector<double> vect = RandomVector(columns);

	//Умножим матрицу
	Matrix result({ rows, columns }, matrix_values);
	result *= vect;

	//Проверим вручную
	for (size_t i = 0; i < rows; i++)
	{
		double reference = 0;
		for (size_t j = 0; j < columns; j++)
		{
			reference += matrix_values[i*columns + j] * vect[j];
		}
		if (Abs (reference - result[i][0]) > Constants::epsiol)
		{
			std::cout << "Failed!";
			return false;
		}
	}

	return true;
}

bool ProcessTestSum()
{
	size_t rows = rand() % MAX_DIM;

	Matrix result({ rows, 1 }, 0);

	std::vector<double> vectors[COUNT_IN_SUM];
	for (int i = 0; i < COUNT_IN_SUM; i++)
	{
		vectors[i] = RandomVector(rows);
		result += vectors[i];
	}

	for (int i = 0; i < rows; i++)
	{
		double reference = 0;
		for (int j = 0; j < COUNT_IN_SUM; j++)
		{
			reference += vectors[j][i];
		}
		if (Abs(reference - result[i][0]) > Constants::epsiol)
		{
			std::cout << "Failed!";
			return false;
		}
	}

	return true;
}

int main()
{
	srand((unsigned int) time(0));

	for (int i = 0; i < COUNT_TESTS; i++)
	{
		if (!ProcessTestMult()) { return ERROR_CODE; }
		if (!ProcessTestSum ()) { return ERROR_CODE; }
	}

	return 0;
}