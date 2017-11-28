#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable ready;

bool data = true;

void ping() {

    while (true) {

        std::unique_lock<std::mutex> lock(m);
        while (!data) {
            ready.wait(lock);
        }

        std::cout << "ping ";
        data = false;
        
        lock.unlock();

        ready.notify_one();
    }
}

void pong() {

    while (true) {

        std::unique_lock<std::mutex> lock(m);
        while (data) {
            ready.wait(lock);
        }

        std::cout << "pong ";
        data = true;
        
        lock.unlock();

        ready.notify_one();
    }
}

int main() {

    std::thread t1(ping);
    std::thread t2(pong);

    t1.join();
    t2.join();
    
    return 0;
}
