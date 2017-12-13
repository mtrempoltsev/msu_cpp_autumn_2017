#include <iostream>
#define _GLIBCXX_HAS_GTHREADS 1
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

std::mutex m;
std::condition_variable ready;
int i = 0;

void ping(){
    while(true){

        std::unique_lock<std::mutex> lock(m);
        cout << "ping ";
        ++i;
        if(i >100){
            return;
        }

    }
}

void pong(){

    while(true){
        std::unique_lock<std::mutex> lock(m);

        cout << "pong ";

        ++i;
        if(i >100){
            return;
        }
    }
}

int main(int argc, char** argv)
{
    cout << "Game starts!" << endl;

    std::thread pongThread(ping);
    std::thread pingThread(pong);

    pingThread.join();
    pongThread.join();
    return 0;
}

