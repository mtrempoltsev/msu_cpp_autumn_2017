#include <iostream>
#include <chrono>
#define NUMBER_OF_ATTEMPTS 5
#define MATRIX_SIZE 31000
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

int main()
{
for (int k=0; k<NUMBER_OF_ATTEMPTS; k++){
    int* matrix = new int [MATRIX_SIZE*MATRIX_SIZE];
    long int sum=0;
    cout<< "Sum by rows:"<<endl;
    for (int i=0; i<MATRIX_SIZE; i++){
            for (int j=0; j<MATRIX_SIZE; j++) matrix[i*MATRIX_SIZE+j]=i*MATRIX_SIZE+j;
    }
    {
        Timer T1;

        for (int i=0; i<MATRIX_SIZE; i++){
            for (int j=0; j<MATRIX_SIZE; j++) sum+=matrix[i*MATRIX_SIZE+j];
        }
    cout<<sum<<endl;
    }
    cout<<"Sum by columns"<<endl;
    sum=0;
    {
        Timer T2;
        for (int i=0; i<MATRIX_SIZE; i++){
            for (int j=0; j<MATRIX_SIZE; j++) sum+=matrix[j*MATRIX_SIZE+i];
        }
    cout<<sum<<endl;
    }
    delete matrix;
}
return 0;
}
