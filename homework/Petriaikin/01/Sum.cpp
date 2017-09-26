#include <chrono>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <climits>
#include <cstring>

//===========================================================================================

#define SIZE 10000
#define MAX_ELEMENT ((int) INT_MAX/SIZE/SIZE) //Чтобы сумма точно поместилась в int

#define COUNT_ITERATIONS 100
#define COUNT_FOR_BOOST 10

#define ERROR_CODE 1

//===========================================================================================

typedef int(*MatrixType) [SIZE];

//===========================================================================================

//Микросекунды stdlib не обнуляются в конструкторе по умолчанию! Поэтому сделаем класс-"декоратор"
typedef class MicrosecondsDefaultZero : public std::chrono::microseconds
{
	public:
		MicrosecondsDefaultZero () : std::chrono::microseconds (std::chrono::microseconds::zero ()) {}
		MicrosecondsDefaultZero (std::chrono::microseconds&& ms) : std::chrono::microseconds (ms) {}
} Microseconds;

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

void FillMatrix(MatrixType matrix) //Заполнение случайными - теперь за приемлимое время, т.к. один раз
{
	assert(matrix != nullptr);
	srand(time(0)); //Генерация новых случайных чисел при каждом запуске программы
	
	std::cout << "Matrix filling ..." << std::endl;

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			matrix [i][j] = (rand())%(MAX_ELEMENT*2+1)-MAX_ELEMENT; //×èñëà [-MAX_ELEMENT;+MAX_ELEMENT]
		}
	}
}

//volatile не даст оптимизатору изменить порядок циклов
int CalculateSumWithProfiling(const /*volatile*/ MatrixType matrix, Microseconds& time, SummType type)
{
	assert(matrix != nullptr && type != SummType::NO_TYPE);

	/*volatile*/ int result = 0;

	//По условиям задачи, работать с массивом как с одномерным нельзя => это недопустимый способ "обмана" компилятора
	//int* matrix_start = (int*) matrix; 

//Макроопределение, которое позволит не дублировать циклы суммирования по строкам и столбцам
//Преимущество: логика суммирования пишется один раз
//Нельзя использовать if (а функция на входе не знает, как ей нужно будет суммировать), т.к. это замедлит цикл
//Использование: SUM_CYCLE(rows, columns) - суммирование по строкам, SUM_CYCLE(columns, rows) - по столбцам
#define SUM_CYCLE(first, second) for (int rows = 0; rows < SIZE; ++rows)\
								 {\
									result += rows;\
									for (int columns = 0; columns < SIZE; ++columns)\
									{\
										result += matrix [first][second];\
									}\
									result -= rows;\
								 }

	Timer timer;
	if (type == SummType::BY_ROWS   ) { SUM_CYCLE(rows, columns); }
	if (type == SummType::BY_COLUMNS) { SUM_CYCLE(columns, rows); }

	time = timer.GetCurrentTime();

//Такое сложное макроопределение лучше удалить
#undef SUM_CYCLE

	return result; 
}

//-------------------------------------------------------------------------------------------

Microseconds MakeTests(int count_tests, SummType type)
{
	MatrixType matrix = (MatrixType) calloc(SIZE*SIZE, sizeof(int));
	assert(matrix != nullptr);
	FillMatrix(matrix); //Будем считать, что скорость суммирования не зависит от содержимого матрицы и для всех итераций будем использовать одну матрицу

	Microseconds sum_time;
	//Сразу и разогрев, и тесты, чтобы не писать дополнительную функцию и 2 цикла
	int count_all = COUNT_FOR_BOOST + count_tests;
	for (int i = 0; i < count_all; ++i)
	{
		Microseconds current_time;
		int result = CalculateSumWithProfiling(matrix, current_time, type);
		std::cout << "Single test: sum = " << result << "; time = " << current_time.count() << " mcs" << std::endl;
		if (i >= COUNT_FOR_BOOST) { sum_time += current_time; } //Boost циклы не считаем
	}

	free(matrix);
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
		return ERROR_CODE;
	}

	std::cout << ((type == SummType::BY_ROWS) ? "Sum by rows" : "Sum by columns") << std::endl;

	Microseconds result = MakeTests(COUNT_ITERATIONS, type);
	double avg_time = ((double) result.count ()) / COUNT_ITERATIONS;

	std::cout << "Result: " << COUNT_ITERATIONS << " tests was processed, summ time = " << result.count() << " microseconds, averege time = ";
	std::cout << std::fixed << std::setprecision (2) << avg_time << " mcs" << std::endl << std::endl;
	
	return 0;
}
