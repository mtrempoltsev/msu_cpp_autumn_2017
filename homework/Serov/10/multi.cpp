#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable dataReady;

bool check = true;

void ping()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(m);
        std::cout << "ping ";
        dataReady.notify_one();
	check = false;
	while (!check)
        	dataReady.wait(lock);
    }
}

void pong()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(m);
        std::cout << "pong ";
        dataReady.notify_one();
	check = true;
	while (check)
        	dataReady.wait(lock);
    }
}

int main(int argc, const char * argv[])
{
    std::thread t1(ping);
    std::thread t2(pong);
    t1.join();
    t2.join();
    return 0;
}


