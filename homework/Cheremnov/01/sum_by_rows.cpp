#include <cstdio>
#include "initial.h"
#include "timer.h"

using namespace std;

//Function for summation of matrix elements on rows
int sum_by_rows(int m[ROWS][COLUMNS])
{
	//In variable s the summation of matrix elements is written
    int s = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
			//i is used for indexing rows, j - for indexing columns
            s += m[i][j];
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
		sum_by_rows(m);
    }
    //Generating the matrix
    set_matrix(m);
    //Starting timer to count time for summation
    Timer *t = new Timer;
    //Generate and summate the matrix
    sum_by_rows(m);
    //Destroying the timer
    delete t;
    //Freeing memory
    delete[] m;
    return 0;
}
