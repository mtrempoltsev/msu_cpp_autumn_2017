#include "ping_pong.hpp"

std::mutex m;
int turn;

void start_ping_pong_game() {
    std::thread t_ping(ping);
    std::thread t_pong(pong);
    t_ping.join();
    t_pong.join();
}


void ping() {
    while (true) {
        m.lock();
        if (turn == Turn::PING) {
            std::cout << "ping" << std::endl;
            turn = Turn::PONG;
        }
        m.unlock();
    }
}


void pong() {
    while (true) {
        m.lock();
        if (turn == Turn::PONG) {
            std::cout << "pong" << std::endl;
            turn = Turn::PING;
        }
        m.unlock();
    }
}
