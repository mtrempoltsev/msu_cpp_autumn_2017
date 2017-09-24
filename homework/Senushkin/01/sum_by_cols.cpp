#include "timer.hpp"

#include <iostream>
#include <cstddef>

#define MAT_SIZE    10000

inline void calc_sum(const int m[][MAT_SIZE], const bool bench_flag = false){
	
	volatile long sum = 0;
	Timer * clock = nullptr;
	
	// benchmsrk mode
	if(bench_flag) 
		clock = new Timer;

	for(std::size_t i = 0; i < MAT_SIZE; i++)
		for(std::size_t j = 0; j < MAT_SIZE; j++)
			// by columns
			sum += m[j][i];

	// free 
	if(clock)
		delete clock;	
}

int main(int argc, char * argv[]){

	// allocation
	auto matrix = new int[MAT_SIZE][MAT_SIZE];
	
	// initialisation
	for(std::size_t i = 0; i < MAT_SIZE; i++)
		for(std::size_t j = 0; j < MAT_SIZE; j++)
			matrix[i][j] = 1;

	// heating cycle
	for(std::size_t t = 0; t < Timer::heat; t++)
		calc_sum(matrix);

	// main loop
	for(std::size_t t = 0; t < Timer::main_loop; t++)
		calc_sum(matrix, true);

	// print average
	std::cout << "Average: " << Timer::run_time / Timer::main_loop << " us" << std::endl;
	
	// free
	delete [] matrix;

	return 0;
}