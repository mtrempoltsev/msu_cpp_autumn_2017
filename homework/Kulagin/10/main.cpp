#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

static bool is_ping_turn;
static int N;

std::condition_variable cond_var;
std::mutex m;

void print_ping() {
    for (int i = 0; i < N; i++) {
        std::unique_lock<std::mutex> lock(m);

        while (!is_ping_turn) {
            cond_var.wait(lock);
        }

        cout << "Ping!" << endl;
        is_ping_turn = false;

        cond_var.notify_one();
    }
}

void print_pong() {
    for (int i = 0; i < N; i++) {
        std::unique_lock<std::mutex> lock(m);

        while (is_ping_turn) {
            cond_var.wait(lock);
        }

        cout << "Pong!" << endl;
        is_ping_turn = true;

        cond_var.notify_one();
    }
}

int main(int argc, char** argv) {
    N = (argc > 1) ? atoi(argv[1]) : 10;

    is_ping_turn = true;

    std::thread ping(print_ping);
    std::thread pong(print_pong);

    ping.join();
    pong.join();

    return 0;
}
