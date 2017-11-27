#include <iostream>
#include <string>

#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std;

enum class Turn
{
    toSay = 0,
    toAnswer = 1,
    toEnd = 2
};

std::mutex mux;
std::condition_variable dataReady;
bool notified = false;
auto turnType = Turn::toSay;

void say(std::string word, bool infinite, int times)
{
    for (int i = 0; i < times || infinite; ++i)
    {
        std::unique_lock<std::mutex> lock(mux);
        std::cout << word << ' ';
        turnType = Turn::toAnswer;
        notified = true;
        dataReady.notify_one();
        dataReady.wait(lock);
    }
    turnType = Turn::toEnd;
    notified = true;
    dataReady.notify_one();
}

void listen_and_answer(std::string word)
{
    std::unique_lock<std::mutex> lock(mux);
    while (!(turnType == Turn::toEnd))
    {
        dataReady.wait(lock, []{return notified;}); // condition to avoid spurious wakeups

        while (turnType == Turn::toAnswer)
        {
            std::cout << word << ' ';
            turnType = Turn::toSay;
        }
        notified = false;
        dataReady.notify_one();
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    bool infinite = true;
    int times = 10;
    if(argc > 1)
    {
        times = atoi(argv[1]);
        if(times > 0)
            infinite = false;
    }
    std::thread t1(say, "ping", infinite, times);
    std::thread t2(listen_and_answer, "pong");

    t1.join();
    t2.join();

    return 0;
}
