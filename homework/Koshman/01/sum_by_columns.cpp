#include <chrono>
#include <iostream>

void print(int ms){
	std::cout << ms / 1000 << ',' << ms % 1000 << " microseconds" << std::endl;
}

int main()
{	
	//matrix size
    const int size = 10 * 1000; 
    //number of test runs
    const int n_runs = 5; 

    typedef std::chrono::high_resolution_clock::time_point time; 

    auto array = new int[size][size];
    volatile long int sum = 0;    
    time start;
    time end;
    int duration = 0;
    int duration_min = (1 << sizeof(int) * 8 - 1) - 1;
    int duration_max = 0;
    int duration_sum = 0;

    //Initialization and warm up
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            array[i][j] = i * size + j;
        }
    }

    std::cout << "summing square matrix of size " << size << " by columns";
    for(int t = 0; t < n_runs; ++t){
        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                sum += array[j][i];
            }
        }
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if (duration < duration_min)
            duration_min = duration;
        if (duration > duration_max)
            duration_max = duration;
        duration_sum += duration;
        sum = 0;
        std::cout << '.';
    }

    duration = duration_sum / n_runs;
    std::cout << std::endl << std::endl;
    std::cout << "fastest:           ";
    print(duration_min);
    std::cout << "slowest:           ";
    print(duration_max);
    std::cout << "average of " << n_runs << " runs: ";
    print(duration);
    delete[] array;
    return 0;
}
