#include <chrono>
#include <iostream>

static std::chrono::high_resolution_clock::duration all_time(0);

class Timer
{
public:
    Timer()
        : start_(std::chrono::high_resolution_clock::now())
    {
    }

    ~Timer()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
		all_time += finish - start_;
    }

    static void print_average_time(int attempts_number)
	{
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(all_time).count() / attempts_number << " us" << std::endl;
    }
			
private:
    std::chrono::high_resolution_clock::time_point start_;	
};	
