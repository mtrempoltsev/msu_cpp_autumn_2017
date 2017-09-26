#include <chrono>
#include <iostream>

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

int main() {
    const int n = 10000;
    
    int** array = nullptr;
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
    
    Timer t;
    volatile int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += array[j][i];
        }
    }
    
    for (int i = 0; i < n; i++) {
        free(array[i]);
    }
    free(array);
    
    return 0;
}
