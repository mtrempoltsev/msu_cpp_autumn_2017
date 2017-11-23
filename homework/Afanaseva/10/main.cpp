#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>

#include <iostream>
#include <string>

#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

int num = 0;
std::mutex mux;
std::condition_variable cond_var;
bool notified = false;
bool done = false;


void say(std::string word, size_t times)
{
    for (size_t i = 0; i < times; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::unique_lock<std::mutex> lock(mux);
        std::cout << word << ' ' << i << ' ';
        num++;
        notified = true;
        cond_var.notify_one();
    }

    done = true;
    num = 1;
    cond_var.notify_one();
}

void listen_and_answer(std::string word)
{
    std::unique_lock<std::mutex> lock(mux);
    while (!done)
    {
        while (!notified) // loop to avoid spurious wakeups
        {
            cond_var.wait(lock);
        }
        while (num == 1)
        {
            std::cout << word << endl;
            num--;
        }
        notified = false;
    }
}


int main()
{
    std::thread t1(say, "ping", 10);
    std::thread t2(listen_and_answer, "pong");

    t1.join();
    t2.join();

    return 0;
}
