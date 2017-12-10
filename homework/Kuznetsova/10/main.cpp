#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mutex;
std::condition_variable cond_var;
bool ping_time = true;

void thread0_ping() {
    while (true) {
        std::unique_lock<std::mutex>
            lock(mutex); /*critical section (exclusive access to std::cout
                            signaled by lifetime of lock) (thanks to
                            cplusplus.com unique_lock example for wording)*/
        std::cout << "ping ";
        ping_time = false;
        cond_var.notify_one();
        while (!ping_time) {
            cond_var.wait(lock);
        }
    }
}

void thread1_pong() {
    while (true) {
        std::unique_lock<std::mutex> lock(mutex);
        while (ping_time) { /* loop to avoid spurious wakeups as said in
                               (thanks to cppreference.com condition_variable
                               example for wording)*/
            cond_var.wait(lock);
        }

        std::cout << "pong ";
        ping_time = true;
        cond_var.notify_one();
    }
}

int main() {
    std::thread t0(thread0_ping);
    std::thread t1(thread1_pong);

    t0.join();
    t1.join();

    return 0;
}
