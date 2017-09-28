/**
 Программы вычисляет сумму элементов матрицы и выводит время этой операции.
 Размер матрицы 10.000 x 10.000.
 Сумма считается по столбцам.
 */
#include <chrono>
#include <iostream>
#include <cstdlib>

const int Size=10000;///< Размер матрицы.

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
    int** A = new int* [Size];
    for(int i = 0; i < Size; i++)
    {
        A[i] = new int [Size];
    }

    // Инициализация.
    for(int i = 0; i < Size; i++)
    {
        for(int j = 0; j < Size; j++)
        {
            A[i][j] = i - j;
        }
    }

    // Вычисление суммы элементов.
    volatile int sum = 0;
    {
        Timer t;
        for(int j = 0; j < Size; j++)
        {
            for(int i = 0; i < Size; i++)
            {
                 sum += A[i][j];
            }
        }
    }
    
    // Высвобождение памяти.
    for(int i = 0; i < Size; i++)
    {
        delete[] A[i];
    }
    delete[] A;

    return 0;
}