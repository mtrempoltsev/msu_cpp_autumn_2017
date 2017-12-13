#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m;
static bool isPing = true;

void ping()
{
    while (true)
    {
        unique_lock<mutex> lock(m);
        if (isPing == true)
        {
            cout << "ping ";
            isPing = false;
        }
    }
}

void pong()
{
    
    while (true)
    {
        unique_lock<mutex> lock(m);
        if (isPing == false)
        {
            cout << "pong ";
            isPing = true;
        }
    }
}

int main(int argc, const char * argv[]) {
    thread t1(ping);
    thread t2(pong);
    t1.join();
    t2.join();
    return 0;
}
