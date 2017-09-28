#include <chrono>
#include <iostream>

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
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};


int main()
{

	volatile static int a[10000][10000];
	volatile long int sum = 0;

    for(int i = 0; i < 10000; ++i) {
        for(int j = 0; j < 10000; ++j) {
            a[i][j] = 1;
        }
    }
	std::cout<<"rows 10000: ";
    auto t = new Timer();
    for(int i = 0; i < 10000; ++i) {
        for(int j = 0; j < 10000; ++j) {
            sum += a[i][j];
        }
    }
    delete t;

    return 0;
}
