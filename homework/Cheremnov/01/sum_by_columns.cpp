#include <cstdio>
#include "initial.h"
#include "timer.h"

using namespace std;

//Function of summation matrix elements on columns
int sum_by_columns(int m[ROWS][COLUMNS])
{
    //In variable s the summation of matrix elements is written
    int s = 0;
    for (int i = 0; i < COLUMNS; i++) {
        for (int j = 0; j < ROWS; j++) {
	    //j is used for indexing rows, i - for indexing columns
            s += m[j][i];
        }
    }
    return s;
}

int main()
{
    //Allocating memory for matrix
    int (*m)[COLUMNS] = new int[ROWS][COLUMNS];
    //Temporary variable, used for warm-uping
    int q;
    //Pre-generate matrix
    set_matrix(m);
    //Warm-up of processor
    for(int i = 1; i < WARMUP_CYCLES; i++){
	//Summate the matrix for warm-uping
	q = sum_by_columns(m);
    }
    //Starting timer to count time for summation
    Timer *t = new Timer;
    //Summate the matrix
    int p = sum_by_columns(m);
    //Test if one returned value from function is equal to another
    if(p != q){
	cout << "Error has been occured";
    }
    else{
	cout << p << endl;
    }
    //Destroying the timer
    delete t;
    //Freeing memory
    delete[] m;
    return 0;
}

