#include <chrono>
#include <iostream>


std::chrono::high_resolution_clock::time_point get_time(){
    return std::chrono::high_resolution_clock::now();
}

// function used in numbers formatting
void print(int ms){
    std::cout << ms / 1000 << ',';
    for (int i = 100; i != 0; i /= 10)
        std::cout <<  (ms % (10 * i)) / i;
    std::cout << " microseconds" << std::endl;
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

    std::cout << "summing square matrix of size " << size << " by rows";
    for(int t = 0; t < n_runs; ++t){
        start = get_time();
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                sum += array[i][j];
            }
        }
        end = get_time();
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

    std::cout << std::endl << std::endl << "summing square matrix of size " << size << " by rows in reverse";
    duration_min = (1 << sizeof(int) * 8 - 1) - 1;
    duration_max = 0;
    duration_sum = 0;
    // rewrite cache
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            array[i][j] = i * size + j;
        }
    }
    for(int t = 0; t < n_runs; ++t){
        start = get_time();;
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                sum += array[size - i - 1][j]; // summing by rows, from last to first
            }
        }
        end = get_time();
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
    
    std::cout << std::endl << std::endl << "summing square matrix of size " << size << " by rows (manually flattened)";
    auto array_flat = (int*) malloc(size * size * sizeof(int));  //continuous chunk of memory
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            array_flat[i * size + j] = i * size + j;
        }
    }
    duration_min = (1 << sizeof(int) * 8 - 1) - 1;
    duration_max = 0;
    duration_sum = 0;
    for(int t = 0; t < n_runs; ++t){
        start = get_time();
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                sum += array_flat[i * size + j];
            }
        }
        end = get_time();
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

    std::cout << std::endl << "Summing in all 3 cases was equally fast. In case of reverse summation it's probably" << std::endl
    << "because frequency of pointer repositioning is still comparably small and" << std::endl
    << "because of cpu/compliler optimizations and in case of flat array -- because" << std::endl
    << "new operator allocates continuous chunks of memory anyway.";
    return 0;
}
