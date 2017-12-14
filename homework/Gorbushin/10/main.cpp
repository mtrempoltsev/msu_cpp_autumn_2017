#include <iostream>
#include <thread>
#include <string>
#include <vector>

const int MAX_PLAYERS = 2;
const int FIRST_PLAYER = 0;

using std::cout;
using std::endl;

std::mutex players[MAX_PLAYERS];

void say(int player_id, const std::string& world) {
    while (1) {
        // Каждый игрок ждет, пока его разблокирует предыдущий
        players[player_id].lock();
        cout << world << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // Разблокировка следующего игрока
        players[(player_id + 1) % MAX_PLAYERS].unlock();
    }
}

int main(void) {
    // Слова, которые говорят треды
    std::vector<std::string> wolrds = { "ping", "pong" };
    
    std::thread threads[MAX_PLAYERS];

    // Лочим все треды, кроме первого игрока
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (i != FIRST_PLAYER) {
            players[i].lock();
        }
        threads[i] = std::thread(say, i, wolrds[i]);
    }
    
    // запускаем игроков
    for (int i = 0; i < MAX_PLAYERS; i++) {
        threads[i].join();
    }
    return 0;
}
