#include <iostream>
#include <chrono>

static const size_t sz = 10000;

// Класс для подсчета промежутка времени; вычисляет разницу во времени между вызовом конструктора и деструктора класса
class Timer {
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

int main(int argc, char** argv) { 
    using TMatrix = int(**);
    using TVector = int(*);
    TMatrix matrix = new TVector[sz];
    
    for (size_t i = 0; i < sz; ++i) {
        matrix[i] = new int[sz];
        for (size_t k = 0; k < sz; ++k) {
            matrix[i][k] = i * sz + k; 
        }
    }
    Timer* t = new Timer();
    size_t sum = 0;
    for (size_t i = 0; i < sz; ++i) {
        for (size_t k = 0; k < sz; ++k) {
            sum += matrix[k][i];
        }
    }
    delete t;
    std::cout << "sum is : " << sum << std::endl;
    for (size_t i = 0; i < sz; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}