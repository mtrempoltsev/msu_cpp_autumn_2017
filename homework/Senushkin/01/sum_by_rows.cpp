#include "timer.hpp"

#include <iostream>
#include <cstddef>

#define MAT_SIZE    10000

inline void calc_sum(const int m[][MAT_SIZE], const bool bench_flag = false){
	if(bench_flag){
		volatile long sum = 0;
		Timer clock = Timer();

		for(std::size_t i = 0; i < MAT_SIZE; i++)
			for(std::size_t j = 0; j < MAT_SIZE; j++)
				// by rows
				sum += m[i][j];
	}else{
		volatile long sum = 0;
		for(std::size_t i = 0; i < MAT_SIZE; i++)
			for(std::size_t j = 0; j < MAT_SIZE; j++)
				sum += m[i][j];
	}		
}

int main(int argc, char * argv[]){

	if(argc > 1){
		std::cout << std::endl << "=====: Launch " << argv[1] << " :=====" << std::endl;
	}

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

	return 0;
}