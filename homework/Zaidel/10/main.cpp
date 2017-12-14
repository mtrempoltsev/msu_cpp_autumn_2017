#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

enum State
{
    Ping,
    Pong
};

State state = State::Ping;

int iteration = 1;
int MAX_ITER = 10;

std::condition_variable cond_var;
std::mutex mutex;

void pong()
{
    while (iteration < MAX_ITER) {
        std::unique_lock<std::mutex> lock(mutex);

        while (state == State::Ping)
            cond_var.wait(lock);

        std::cout <<"pong" << std::endl;
        state = State::Ping;
        iteration++;

        mutex.unlock();
        cond_var.notify_one();
    }
}

void ping()
{
    while (iteration < MAX_ITER) {
        std::unique_lock<std::mutex> lock(mutex);

        while (state == State::Pong)
            cond_var.wait(lock);

        std::cout <<"ping" << std::endl;
        state = State::Pong;
        iteration++;


        mutex.unlock();
        cond_var.notify_one();
    }
}




int main() {

    std::thread t2(ping);
    std::thread t1(pong);


    t2.join();
    t1.join();

    return 0;
}