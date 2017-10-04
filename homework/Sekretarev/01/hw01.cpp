#include <iostream>
#include <chrono>

using namespace std;

class Timer {
public:
    Timer()
        : start_(std::chrono::high_resolution_clock::now())
    {
    }

	int stop() {
		const auto finish = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count();
	}
    ~Timer()
    {
        //const auto finish = std::chrono::high_resolution_clock::now();
        //std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};
const int n_runs = 100;
const int n = 10000;
const int m = 10000;

int main() {
    int** mass;
    mass = new int*[n];
    for(int i = 0; i < n; i++) {
    	mass[i] = new int[m];
    	for(int j = 0; j < m; j++) {
    		mass[i][j] = (i + 22) * (j - 62) % 10000;
    	}
    }
    
    
    {
	    double time;
	    for(int k = 0; k < n_runs; k++) {
	    	volatile int sum = 0;
	    	Timer t;
	    	for(int i = 0; i < n; i++) {
	    		for(int j = 0; j < m; j++) {
	    			sum += mass[i][j];
	    		}
	    	}
	    	int tmp = t.stop();
	    	time = (time * k + tmp) / (k + 1);
	    }
	    std::cout << "after " << n_runs << " runs (i -> j) average time = " << (int)time << std::endl;
	}
    
    {
	    double time;
	    for(int k = 0; k < n_runs; k++) {
	    	volatile int sum = 0;
	    	Timer t;
	    	for(int i = 0; i < n; i++) {
	    		for(int j = 0; j < m; j++) {
	    			sum += mass[j][i];
	    		}
	    	}
	    	int tmp = t.stop();
	    	time = (time * k + tmp) / (k + 1);
	    }
	    std::cout << "after " << n_runs << " runs (j -> i) average time = " << (int)time << std::endl;
	}
	
	return 0; 
}
