#pragma once
#include <cstdlib>
#include <ctime>

enum
{
	//Number of rows
	ROWS = 10000,
	
	//Number of columns
	COLUMNS = 10000,
	
	//Number of cycles of warm-up
	WARMUP_CYCLES = 10
};
// Function for random filling of matrix elements
void set_matrix(int m[ROWS][COLUMNS]){
	//Initialising random
	srand(time(0));
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLUMNS; j++){
			//Generating random numbers from 0 to 9
			m[i][j] = rand() % 10;
		}
	}
}
