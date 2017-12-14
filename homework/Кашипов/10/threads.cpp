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
