#include <iostream>
#include <chrono>
#include <iostream>
using namespace std;
int N=10000;
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
double sum=0;
double* matrix = new double[N*N];
 
if (matrix==nullptr)
 {
  cout << "Error" << endl;
  return 0;
 }

for(i=0;i<N;i++)
 for(j=0;j<N;j++)
 {
  matrix[i*N+j]=rand()%100;
  //cout << "matrix["<< i <<"]="<< matrix[i] << endl;
 }


{
 Timer* T = new Timer() ;
 for(i=0;i<N;i++)
  for(j=0;j<N;j++)
   sum+=matrix[i*N+j];
 cout << "Matrix sum = " << sum <<endl;
 delete T;
}



free(matrix);
return 1;	
}
