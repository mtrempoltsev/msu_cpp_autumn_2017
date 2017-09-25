#include "timer.hpp"

int main()
{
for (int k=0; k<NUMBER_OF_ATTEMPTS; k++){
    int* matrix = new int [MATRIX_SIZE*MATRIX_SIZE];
    volatile long int sum=0;
    for (int i=0; i<MATRIX_SIZE; i++){
            for (int j=0; j<MATRIX_SIZE; j++) matrix[i*MATRIX_SIZE+j]=i*MATRIX_SIZE+j;
    }
    {
        Timer T1;

        for (int i=0; i<MATRIX_SIZE; i++){
            for (int j=0; j<MATRIX_SIZE; j++) sum+=matrix[i*MATRIX_SIZE+j];
        }
    }
    delete matrix;
}
std::cout << "Average time of summation by rows" << std::endl;
std::cout << all_time/NUMBER_OF_ATTEMPTS <<" us"<< std::endl;
return 0;
}
