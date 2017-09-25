#include <chrono>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <climits>

//===========================================================================================

#define SIZE 10000
#define MAX_ELEMENT ((int) INT_MAX/SIZE/SIZE) //Чтобы сумма точно поместилась в int

#define COUNT_ITERATIONS 100
#define COUNT_FOR_BOOST 10

//===========================================================================================

typedef std::chrono::microseconds Microseconds;
typedef int(*MatrixType) [SIZE];

//===========================================================================================

class Timer
{
	private:
		const std::chrono::high_resolution_clock::time_point start_;

	public:
		Timer();

		Microseconds GetCurrentTime();
};

Timer::Timer() : start_ (std::chrono::high_resolution_clock::now())
{}

Microseconds Timer::GetCurrentTime()
{
	const auto finish = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(finish - start_);
}

//===========================================================================================

enum SummType
{
	NO_TYPE = 0,
	BY_ROWS = 1,
	BY_COLUMNS = 2
};

//===========================================================================================

void MakeMatrix(MatrixType matrix) //Заполнение случайными - очень долго
{
	assert(matrix != nullptr);

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			matrix [i][j] = (i*j+i+j)%MAX_ELEMENT;
			if ((i*j) % 7 == 0) //Пусть некоторые числа будут отрицательными
			{
				matrix [i][j] *= -1;
			}
		}
	}
}

//volatile не даст оптимизатору изменить порядок циклов
int CalculateSumRowsWithProfiling(const /*volatile*/ MatrixType matrix, Microseconds& current_time, SummType type)
{
	assert(matrix != nullptr && type != SummType::NO_TYPE);

	/*volatile*/ int result = 0;

	//Будем делать адресацию арифметикой указателей - это не потребует не так много доп. времени как volatile, но не даст оптимизировать порядок циклов
	int* matrix_start = (int*) matrix; 
	
	Timer timer;
	if (type == SummType::BY_ROWS)
	{
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				result += *(matrix_start + i*SIZE + j);
				//result += matrix [i][j];
			}
		}
	}
	if (type == SummType::BY_COLUMNS)
	{
		int* m = (int*) matrix;
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				result += *(matrix_start + j*SIZE + i);
				//result += matrix [j][i];
			}
		}
	}
	current_time = timer.GetCurrentTime();

	return result; 
}

//-------------------------------------------------------------------------------------------

void MakeSingleTest(Microseconds& sum_time, SummType type)
{
	assert(type != SummType::NO_TYPE);

	MatrixType matrix = (MatrixType) calloc(SIZE*SIZE, sizeof (int));
	assert(matrix != nullptr);
	MakeMatrix(matrix);

	Microseconds current_time;
	int result = CalculateSumRowsWithProfiling(matrix, current_time, type);
	std::cout << "Single test: sum = " << result << "; time = " << current_time.count() << " mcs" << std::endl;
	sum_time += current_time;

	free(matrix);
}

Microseconds MakeMultipleTests(int count_tests, SummType type)
{
	Microseconds sum_time;

	for (int i = 0; i < COUNT_FOR_BOOST; ++i) //Разогрев
	{
		MakeSingleTest(sum_time, type);
	}
	sum_time = Microseconds::zero();

	for (int i = 0; i < count_tests; ++i)
	{
		MakeSingleTest(sum_time, type);
	}

	return sum_time;
}

//===========================================================================================

int main(int count_args, char* args [])
{
	SummType type = SummType::NO_TYPE;
	if (count_args > 1)
	{
		if (strcmp(args [1], "-c") == 0) { type = SummType::BY_COLUMNS; }
		if (strcmp(args [1], "-r") == 0) { type = SummType::BY_ROWS;    }
	}
	if (type == SummType::NO_TYPE)
	{
		std::cout << "-r (sum by rows) or -c (sum by columns) is required as the first argument!";
		return 0;
	}

	std::cout << ((type == SummType::BY_ROWS) ? "Sum by rows" : "Sum by columns") << std::endl;

	std::string filename;
	if (type == SummType::BY_ROWS) { filename = "rowsresults.txt"; }
	else { filename = "columnsresults.txt"; }

	std::fstream file;
	file.open(filename, std::fstream::app);

	Microseconds result = MakeMultipleTests(COUNT_ITERATIONS, type);
	double avg_time = ((double) result.count ()) / COUNT_ITERATIONS;

	std::cout << COUNT_ITERATIONS << " tests was processed, summ time = " << result.count() << " microseconds, averege time = ";
	std::cout << std::fixed << std::setprecision (2) << avg_time << " mcs";
	time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	file << std::put_time(std::localtime (&current_time), "%c") << '\t' << COUNT_ITERATIONS << '\t' << result.count () << '\t';
	file << std::fixed << std::setprecision(2) << avg_time << " mcs" << std::endl;

	file.close();
	
	return 0;
}
