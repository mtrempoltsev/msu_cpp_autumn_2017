#include "timer.h"

int main()
{
    int* array[rows];
    
    for (int i = 0; i < rows; i++)
        	array[i] = new int [columns];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            array[i][j] = ((rand() % 10));

	volatile int sum = 0;
	
	//================================
	
	Timer* T = new Timer();

 	for (int i = 0; i < columns; i++)
		for (int j = 0; j < rows; j++)
			sum += array[j][i];

	delete T;
	
	//================================
    
    for (int i = 0; i < rows; i++)
        	delete [] array[i];

	return 0;
}