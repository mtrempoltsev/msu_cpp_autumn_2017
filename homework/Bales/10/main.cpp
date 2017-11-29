#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cond_var;
static bool isPing = true;

void ping() {
    static int cnt = 10;
    while (cnt > 0) {
        std::unique_lock<std::mutex> lock(m);
        while (!isPing) {
            cond_var.wait(lock);
        }        
        std::cout << "ping ";
        isPing = !isPing;
        cnt--;
        cond_var.notify_one();
    }
}

void pong() {
    static int cnt = 10;
    while (cnt > 0) {
        std::unique_lock<std::mutex> lock(m);
        while (isPing) {
            cond_var.wait(lock);
        }        
        std::cout << "pong\n";
        isPing = !isPing;
        cnt--;
        cond_var.notify_one();
    }
}

int main(int argc, char* argv[]) 
{
    std::thread t1(ping);
    std::thread t2(pong);
    t1.join();
    t2.join();
    return 0;
}