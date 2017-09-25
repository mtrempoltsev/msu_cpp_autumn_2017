#include "timer.hpp"
#include "constants.hpp"
#include <vector>
using namespace std;
int main()
{
    //Инициализация матрицы
    vector<vector<int>> matrix (MATRIX_SIZE, vector<int>(MATRIX_SIZE,0));
    volatile long int sum=0;
    for (int i=0; i<MATRIX_SIZE; i++){
            for (int j=0; j<MATRIX_SIZE; j++) matrix[i][j]=i*MATRIX_SIZE+j;
    }
    //Подсчет суммы
    for (int k=0; k<NUMBER_OF_ATTEMPTS; k++){

        Timer T;

        for (int i=0; i<MATRIX_SIZE; i++){
            for (int j=0; j<MATRIX_SIZE; j++) sum+=matrix[i][j];
        }
        sum=0;
    }
std::cout << "Average time of summation by rows" << std::endl;
std::cout << all_time/NUMBER_OF_ATTEMPTS <<" us"<< std::endl;
return 0;
}
