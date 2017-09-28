/**
 Программы вычисляет сумму элементов матрицы и выводит время этой операции.
 Размер матрицы 10.000 x 10.000.
 Сумма считается по столбцам.
 */
#include <chrono>
#include <iostream>
#include <cstdlib>

#define SIZE 10000 ///< Размер матрицы.

/**
 Класс для измерения времени. 
 Создание экземпляра класса - начало отсчета.
 Уничтожение экземпляра класса - окончание отсчета и вывод пройденного времени в стандартный поток вывода.
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


int main(int argc, char** argv)
{
    // Выделение памяти.
    int* A = (int *)malloc(sizeof(int) * SIZE * SIZE);

    // Инициализация.
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            A[i*SIZE + j] = i - j;
        }
    }

    // Вычисление суммы элементов.
    volatile int sum = 0;
    Timer t;
    for(int j = 0; j < SIZE; j++)
    {
        for(int i = 0; i < SIZE; i++)
        {
             sum += A[i*SIZE + j];
        }
    }
    
    return 0;
}