//
//  main.cpp
//  TS
//
//  Created by Максим on 21.09.17.
//  Copyright © 2017 Максим. All rights reserved.
//

#include <iostream>


#define M 10000
#define N 10000
#define MIN -100
#define MAX 100

using namespace std;


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


//функция суммирования эдементов матрицы по строкам
long long int sum_rows(int** matrix, int m, int n) {
    volatile long long int sum = 0;
    Timer t;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

int main(int argc, const char * argv[]) {
    
    int** matrix = new int* [M];
    
    //выделение памяти
    for (int i = 0; i < M; i++) {
        matrix[i] = new int [N];
    }
    
    //инициализация матрицы случайными числами
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = arc4random() % 2 ? (arc4random() % 100) : -(arc4random() % 100);
        }
    }
    
    
    cout << sum_rows(matrix, M, N) << endl;
    
    //освобождение памяти
    for (int i = 0; i < M; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
    
    return 0;
}
