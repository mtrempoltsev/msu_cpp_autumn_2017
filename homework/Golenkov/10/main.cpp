#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable cond_var;
std::mutex m;

bool isPonged = true;
int N = 100;

void printPing()
{
    for (int i = 0; i < N; i++)
    {
        std::unique_lock<std::mutex> lock(m);
        while (!isPonged)
        {
            cond_var.wait(lock);
        }
        std::cout << "ping" << std::endl;
        isPonged = false;
        cond_var.notify_one();
    }
}

void printPong()
{
    for (int i = 0; i < N; i++)
    {
        std::unique_lock<std::mutex> lock(m);
        while (isPonged)
        {
            cond_var.wait(lock);
        }
        std::cout << "pong" << std::endl;
        isPonged = true;
        cond_var.notify_one();
    }
}

int main() {
    std::thread t1(printPing);
    std::thread t2(printPong);
    t1.join();
    t2.join();
    return 0;
}
