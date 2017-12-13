#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
static bool isPing = true;
std::condition_variable cond_var;

void ping() {
    static int count = 20;
    while (count > 0) {
        std::unique_lock<std::mutex> lock(m);
        while (!isPing) {
            cond_var.wait(lock);
        }        
        std::cout << "ping ";
        isPing = !isPing;
        count--;
        cond_var.notify_one();
    }
}

void pong() {
    static int count = 20;
    while (count > 0) {
        std::unique_lock<std::mutex> lock(m);
        while (isPing) {
            cond_var.wait(lock);
        }        
        std::cout << "pong \n";
        isPing = !isPing;
        count--;
        cond_var.notify_one();
    }
}

int main(int argc, const char * argv[]) {
    std::thread t1(ping);
    std::thread t2(pong);
    t1.join();
    t2.join();
    return 0;
}