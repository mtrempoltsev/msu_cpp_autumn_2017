#include <chrono>
#include <iostream>

//Класс таймера, который замеряет время, прощедшее между созданием переменной типа Timer и
//вызовом метода stop()
class Timer
{
public:
    Timer()
    : start_(std::chrono::high_resolution_clock::now())
    {
    }
    
    ~Timer()
    {
    }
    
    double stop()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
        return (finish - start_).count();
    }
    
private:
    const std::chrono::high_resolution_clock::time_point start_;
};

int main() {
    const int n = 10000;      // Размерность матрицы, которую суммируем
    const int hot_runs = 20;  // Количество прогонов для замера производительности
    const int cold_runs = 5;  // Количество прогонов для прогрева процессора
    int** array = nullptr;    // Матрица, в которой хранятся значения
    
    // Выделяем память сначала под все строки матрицы(указатели),
    // потом для каждой строки и заполняем матрицу 1
    array = (int**)malloc(n*sizeof(int*));
    if (array == nullptr) {
        std::cout << "Memory error!" << std::endl;
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        array[i] = (int*)malloc(n*sizeof(int));
        if (array[i] == nullptr) {
            std::cout << "Memory error!" << std::endl;
            return 1;
        }
        for (int j = 0; j < n; j++) {
            array[i][j] = 1;
        }
    }
    
    // Выполняем прогревочные прогоны
    for (int k = 0; k < cold_runs; k++) {
        volatile int sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                sum += array[i][j];
            }
        }
    }
    
    // Запускаем таймер и начинаем замер производительности
    Timer t;
    volatile int sum = 0;
    for (int k = 0; k < hot_runs; k++) {
        sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                sum += array[i][j];
            }
        }
    }
    
    // Выводим результат, нормированный для 1 прогона и
    // освобождаем ранее выделенную память
    std::cout << std::fixed << t.stop()/hot_runs << " us" << std::endl;
    for (int i = 0; i < n; i++) {
        free(array[i]);
    }
    free(array);
    
    return 0;
}
