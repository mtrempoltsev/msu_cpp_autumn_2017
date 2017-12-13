#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>


std::mutex m;
std::condition_variable cond_var;
bool notified = false;

void ping() {
    while (1) {
        std::unique_lock<std::mutex> lock(m);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        std::cout << "ping\n";
        
        notified = true;
        cond_var.notify_one();
    }
}

void pong() {
    while (1) {
        std::unique_lock<std::mutex> lock(m);
        
        while (!notified) {  // loop to avoid spurious wakeups
            cond_var.wait(lock);
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        std::cout << "pong\n";
        notified = false;
        cond_var.notify_one();
        
    }
}


int main()
{
    std::thread t1(ping);
    std::thread t2(pong);
    
    t1.join();
    t2.join();
}
