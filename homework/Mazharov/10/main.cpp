#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;

void ping() {
    while (true) {
        std::unique_lock<std::mutex> lock(m);
        std::cout << "ping\n";
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        cv.notify_one();
    }
}

void pong() {
    while (true) {
        std::unique_lock<std::mutex> lock(m);
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "pong\n";
        cv.notify_one();
    }
}

int main() {
    std::thread t1(ping);
    std::thread t2(pong);
    t1.join();
    t2.join();
    return 0;
}