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
    int (*m)[COLUMNS] = new int[ROWS][COLUMNS];
    //Temporary variable, used for warm-uping
    int q;
    //Pre-generate matrix
    set_matrix(m);
    //Warm-up of processor
    for(int i = 1; i < WARMUP_CYCLES; i++){
	//Summate the matrix for warm-uping
	q = sum_by_rows(m);
    }
    //Starting timer to count time for summation
    Timer *t = new Timer;
    //Summate the matrix
    int p = sum_by_rows(m);
    //Test if one returned value from function is equal to another
    if(p != q){
	cout << "Error has occured";
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
