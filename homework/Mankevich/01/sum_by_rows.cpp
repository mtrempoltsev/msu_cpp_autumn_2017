#include <chrono>
#include <iostream>

#define SIZE 10000

class Timer{
    public:
        Timer()
            : start_(std::chrono::high_resolution_clock::now()){
        }

        ~Timer(){
            const auto finish = std::chrono::high_resolution_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
        }
    
    private:
        const std::chrono::high_resolution_clock::time_point start_;
};

int main(){
    int* arr = new int[SIZE * SIZE];
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            arr[i * SIZE + j] = i + j;
        }
    }
    volatile int sum = 0;
    Timer t;
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            sum += arr[i * SIZE + j];
        }
    }
    delete []arr;
    return 0;
}