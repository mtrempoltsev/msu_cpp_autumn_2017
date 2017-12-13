#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>

std::mutex mutex;
std::condition_variable cond_var;
bool is_ping = true;

void ping_pong(bool ping_action)
{
    while (true)
    {
        {
            // дополнительный блок для того, чтобы mutex разлочился перед notify_one
            // хотя работает и без этого, но без этого скорей всего будет тормозить wait при попытке залочить mutex
            std::unique_lock<std::mutex> lock(mutex);

            while (is_ping != ping_action)
                cond_var.wait(lock);

            std::cout << ((ping_action)? "ping" : "pong") << std::endl;
            is_ping = !is_ping;
        }

        cond_var.notify_one();
    }
}

int main(){
    std::thread t1(ping_pong, true);
    std::thread t2(ping_pong, false);
    t1.join();
    t2.join();
    return 0;
}
