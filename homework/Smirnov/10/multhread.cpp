#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <string>

std::mutex mutex;
std::condition_variable condition;

void thread(std::string text)
{
	while(true)
	{	
		std::unique_lock<std::mutex> lock{mutex};
		std::cout << text << " ";
		condition.notify_one();
		condition.wait(lock);
	}
}

int main(int argc, char** argv)
{
	std::thread t1(thread, "ping");
	std::thread t2(thread, "pong");

	t1.join();
	t2.join();

	return 0;
}