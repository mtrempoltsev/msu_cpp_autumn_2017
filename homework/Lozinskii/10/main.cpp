#include <iostream>
#include <thread>
#include <string>
#include <sched.h>
int locker = 1;

void say (int id, std::string str) {
    while (true) {
        if (locker == id) {
            std::cout<< str;
            locker ^= 1;
        }
        sched_yield();
    }
}

int main() {
    std::thread t1(say, 1, "ping ");
    std::thread t2(say, 0, "pong ");

    t1.join();
    t2.join();
    return 0;
}