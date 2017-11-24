// Vasilii Bodnariuk
#include <iostream>
#include <chrono>

#include <condition_variable>
#include <mutex>
#include <thread>

int main()
{
    std::mutex m;
    std::condition_variable cond_var;
    bool pinged = false; // var to avoid spurious wakeups

    std::thread t_ping([&]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::unique_lock<std::mutex> lock(m);
            std::cout << "ping" << '\n';
            pinged = true;
            cond_var.notify_one();
        }

        cond_var.notify_one();
    });

    std::thread t_pong([&]() {
        std::unique_lock<std::mutex> lock(m);
        while (!pinged) {
            cond_var.wait(lock);
            std::cout << "pong" << '\n';
            pinged = false;
        }
    });

    t_ping.join();
    t_pong.join();
}
