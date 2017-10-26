#include "Matrix.h"
#include "Matrix.hpp"
#include <time.h>

//========================================================================

#define ERROR_CODE 1
#define COUNT_TESTS 10

#define MAX_DIM 100
#define MAX_RAND 10000
#define COUNT_IN_SUM 10

#define RANDOM_T ((T) (rand()%MAX_RAND))

//========================================================================

template<typename T>
std::vector<T> RandomVector(size_t size)
{
	std::vector<T> result(size, 0);
	for (size_t i = 0; i < size; i++)
	{
		T divider = RANDOM_T;
		if (divider == 0) { divider = 1; }
		result[i] = RANDOM_T*RANDOM_T / divider;
	}

	return result;
}

template<typename T>
bool ProcessTestMult()
{
	size_t rows = rand() % MAX_DIM;
	size_t columns = rand() % MAX_DIM;

	std::vector<T> matrix_values = RandomVector<T>(rows*columns);
	std::vector<T> vect = RandomVector<T>(columns);

	//Умножим матрицу
	Matrix<T> result({ rows, columns }, matrix_values);
	result *= vect;

	//Проверим вручную
	for (size_t i = 0; i < rows; i++)
	{
		T reference = 0;
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

template<typename T>
bool ProcessTestSum()
{
	size_t rows = rand() % MAX_DIM;

	Matrix<T> result({ rows, 1 }, 0);

	std::vector<T> vectors[COUNT_IN_SUM];
	for (int i = 0; i < COUNT_IN_SUM; i++)
	{
		vectors[i] = RandomVector<T>(rows);
		result += vectors[i];
	}

	for (size_t i = 0; i < rows; i++)
	{
		T reference = 0;
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
		if (!ProcessTestMult<double>()) { return ERROR_CODE; }
		if (!ProcessTestSum<double> ()) { return ERROR_CODE; }
		if (!ProcessTestMult<int>())    { return ERROR_CODE; }
		if (!ProcessTestSum<int>())     { return ERROR_CODE; }
	}

	//Проверим, не утекла ли память
	if (Matrix<double>::GetMemoryAllocated() != 0)
	{
		std::cout << "Memory leak!" << std::endl;
		return ERROR_CODE;
	}

	return 0;
}