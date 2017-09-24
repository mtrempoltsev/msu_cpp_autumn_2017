#include <cstdio>
#include "initial.h"
#include "timer.h"

using namespace std;

//Function of summation matrix elements on columns
int sum_by_columns(int m[ROWS][COLUMNS])
{
    volatile int s = 0;
    for (int i = 0; i < COLUMNS; i++) {
        for (int j = 0; j < ROWS; j++) {
            s += m[j][i];
        }
    }
    return s;
}

int main()
{
	//Allocating memory for matrix
    int (*m)[ROWS] = new int[ROWS][COLUMNS];
    //Warm-up of processor
    for(int i = 1; i < WARMUP_CYCLES; i++){
		//Generate and summate the matrix for warm-uping
		set_matrix(m);
		sum_by_columns(m);
    }
    //Generating the matrix
    set_matrix(m);
    //Starting timer to count time for summation
    Timer *t = new Timer;
    //Generate and summate the matrix
    sum_by_columns(m);
    //Destroying the timer
    delete t;
    //Freeing memory
    delete[] m;
    return 0;
}

