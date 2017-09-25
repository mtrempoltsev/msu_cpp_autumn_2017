#include <iostream>
#include <chrono>

#define N 10000
#define MAX_ITERATIONS 10

using namespace std;

int main() {
	int** data = (int**)malloc(N * sizeof(int*));
	
	for(int i = 0; i < N; i++) {
		data[i] = (int*)malloc(N * sizeof(int));
	}
	
	srand((unsigned)time(0));
	
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			data[i][j] = rand();
		}
	}
	
	auto t = 0;
	
	for(int _ = 0; _ < MAX_ITERATIONS; _++) {
		volatile long int sum = 0;
		
		auto t1 = std::chrono::high_resolution_clock::now();
		
		for(int j = 0; j < N; j++) {
			for(int i = 0; i < N; i++) {
				sum += data[i][j];
			}
		}
		
		auto t2 = std::chrono::high_resolution_clock::now();
		
		t += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	}
	
	cout << t / MAX_ITERATIONS << " us" << endl;
	
	// cout << sum << endl;
	
	for(int i = 0; i < N; i++) {
		delete[] data[i];
	}
	
	delete[] data;
	
	return 0;
}
