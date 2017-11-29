#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>

std::mutex mutex;
std::condition_variable cond_var;
int is_ping = 1;

void ping_pong(int action)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mutex);

        while (is_ping * action == -1)
            cond_var.wait(lock);

        std::cout << ((action == 1)? "ping" : "pong") << std::endl;
        is_ping *= -1;

        cond_var.notify_one();
    }
}

int main(){
    std::thread t1(ping_pong, 1);
    std::thread t2(ping_pong, -1);
    t1.join();
    t2.join();
    return 0;
}
