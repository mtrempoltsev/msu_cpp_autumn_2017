#include <iostream>
#include <chrono>

using namespace std;
int n=10000;
int a[10000][10000];

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
   int i=0;
   int j=0;
   for(i=0;i<n;i++){
       for(j=0;j<n;j++) a[i][j]=1;
   }
   int sum=0;
   Timer t;
   for(i=0;i<n;i++){
       for(j=0;j<n;j++) sum=sum+a[j][i];
   }
   cout<<sum<<endl;
}
