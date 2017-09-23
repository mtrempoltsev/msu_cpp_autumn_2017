#include <iostream>
// #include <random>
#include <chrono>

static const size_t sz = 10000;

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

// void print(const int* arr) {
//     for (size_t i = 0; i < sz; ++i) {
//         for (size_t j = 0; j < sz; ++j) {
//             std::cout << arr[i * sz + j] << " ";
//         }
//         std::cout << std::endl;
//     }
//     std::cout << "***************" << std::endl;
// }

int main(int argc, char** argv) { 
    // std::random_device device;
    // std::minstd_rand gen(device());
    // std::uniform_int_distribution<int> distrib(1, 1000);

    Timer t;
    using TMatrix = int[sz * sz];
    int* matrix = new TMatrix;
    
    for (size_t i = 0; i < sz; ++i) {
        for (size_t k = 0; k < sz; ++k) {
            matrix[i * sz + k] = i * sz + k; 
        }
    }

    for (size_t i = 0; i < sz; ++i) {
        for (size_t k = 0; k < sz; ++k) {
            matrix[i * sz + k] += matrix[i * sz + k]; 
        }
    }
    // print(matrix);
    delete[] matrix;
    return 0;
}