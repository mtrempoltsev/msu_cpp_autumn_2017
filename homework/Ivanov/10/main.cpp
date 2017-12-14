#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>

const int MAX_PLAYERS = 2;
const int FIRST_PLAYER = 0;

using std::cout;
using std::endl;

std::mutex players[MAX_PLAYERS];

void tail(int id, const std::string& name) {
    while (1) {
        players[id].lock();
        cout << name << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        players[(id + 1) % MAX_PLAYERS].unlock();
    }
}

int main(void) {
    std::vector<std::string> names = { "ping", "pong" };
    std::thread thd[MAX_PLAYERS];
    for(int i = 0; i < MAX_PLAYERS; i++) {
        if(i != FIRST_PLAYER) {
            players[i].lock();
        }
        thd[i] = std::thread(tail, i, names[i]);
    }
    for(int i = 0; i < MAX_PLAYERS; i++) {
        thd[i].join();
    }
    return 0;
}
