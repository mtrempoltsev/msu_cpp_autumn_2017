#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable dataReady;

void thread(std::string data)
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(m);
        std::cout << data;
        dataReady.notify_one();
        dataReady.wait(lock);
    }
}

int main(int argc, const char * argv[])
{
    std::thread t1(thread, "ping ");
    std::thread t2(thread, "pong ");
    t1.join();
    t2.join();
    return 0;
}
