#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <functional>

using CondVar = std::condition_variable;
using Mut = std::mutex;

Mut mutex;

int flag = 1;

//thread function, it writes "ping" or "pong" depending on which process calls it
void ping_pong(CondVar &own, CondVar &foreign, int condition)
{
  while(true){
    std::unique_lock<Mut> lock{mutex};
    // lock the specific mutex and wait until this process' condition_variable
    // is available
    while (flag != condition){
        own.wait(lock);
    }
    // write specific string and change the flag
    if (flag == 1) {
      std::cout << "ping ";
      flag = 2;
    } else {
      std::cout << "pong ";
      flag = 1;
    }
    // notify other process to stop waiting
    foreign.notify_one();
  }
  return;
}

int main()
{
    Mut ping_mutex;
    Mut pong_mutex;
    CondVar ping_ready;
    CondVar pong_ready;
    //bind two functions based on ping_pong with different parameters
    auto ping = std::bind(ping_pong, std::ref(ping_ready), std::ref(pong_ready), 1);
    auto pong = std::bind(ping_pong, std::ref(pong_ready), std::ref(ping_ready), 2);
    // start threads
    std::thread t1(ping);
    std::thread t2(pong);
    // wait in main process until t1 and t2 end
    t1.join();
    t2.join();
    return 0;
}
