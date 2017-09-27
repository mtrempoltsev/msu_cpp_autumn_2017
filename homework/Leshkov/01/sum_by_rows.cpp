#include <iostream>
#include <cstdlib>
#include <chrono>
#define msize 10000
#define launches 10


long int avg_time=0;
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
        ::avg_time+=std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};




int main(){


for (int k=0;k!=launches;k++){

		{
			int** a=new int*[msize];
			for(int i=0; i!=msize; i++)
				a[i]=new int[msize];

			Timer* t=new Timer;

			volatile int sum=0;
			for (int i=0; i!=msize; i++){
				for (int j=0; j!=msize; j++){
					sum+=a[i][j];
				}
			}
			delete t;
			for(int i=0; i!=msize; i++)
				delete[] a[i];
			delete[] a;
		}
		
	}
	std::cout<<"avg_time from "<<launches<<" starts = "<<avg_time/launches<<" us"<<std::endl;

	return 0;
}