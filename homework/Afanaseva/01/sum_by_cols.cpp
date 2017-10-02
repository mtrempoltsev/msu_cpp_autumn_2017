#include <chrono>
#include <iostream>
#include <ctime>

using namespace std;
// Инициализация параметров запуска программы: размер квадратной матрицы и число итераций прогрева
namespace options
{
    const int size_of_matrix = 10000;
    const int warmup_constant = 100;
}

/* Класс для замера времени работы программы.
 *  При уничтожении экземпляра класса происходит запись в терминал
 * времени между вызовами конструктора и деструктора класса.
 */
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


// Фунция инициализации массива данных случайным образом
void init_array(int n, int** array)
{
    srand(time(NULL));
    for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
	    array[i][j] = rand() % 7;
}

// Функция суммирования значений массива по строкам
int sum_by_cols(int n, int** array)
{
    volatile int sum = 0;
    for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
	    sum += array[j][i];
    return sum;
}

//-----------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    //Инициализация констант (можно было не делать)
    const int n = options::size_of_matrix;
    const int warmup = options::warmup_constant;

    //Cоздание и заполнение массива
    int** array = new int*[n];
    for(int i = 0; i < n; i++)
	    array[i] = new int[n];

    init_array(n, array);

    //Прогрев кэша
    for(int i = 0; i < warmup; i++)
	sum_by_cols(n, array);

    volatile int sum = 0;

    //Начало отсчета времени суммирования
    Timer *t = new Timer();

    sum = sum_by_cols(n, array);

    //Завершение отсчета времени суммирования
    delete t;

    //Освобождение памяти
    for(int i = 0; i < n; i++)
	delete[] array[i];

    delete[] array;
    return 0;
}
