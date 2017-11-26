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
        std::lock_guard<std::mutex> lock(m);
        if (turn == Turn::PING) {
            std::cout << "ping" << ' ';
            turn = Turn::PONG;
        }
    }
}


void pong() {
    while (true) {
        std::lock_guard<std::mutex> lock(m);
        if (turn == Turn::PONG) {
            std::cout << "pong" << ' ';
            turn = Turn::PING;
        }
    }
}
