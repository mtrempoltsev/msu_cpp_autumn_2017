#include<thread>
#include<iostream>
#include<atomic>




bool flag = false;


void thread1()
{
while(true)
	{
		if (!flag)
			{
				std::cout << "ping"<< std::endl;
                                flag = true;
				//RELEASE_FENCE;
			}
	} 
}


void thread2()
{
while(true)
	{
		if (flag)
			{
				std::cout << "pong"<< std::endl;
				flag = false;
				//RELEASE_FENCE;
			}
	} 
}

int main()
{
std::thread t(thread1);
std::thread l(thread2);

t.join();
l.join();
return 1;
}
