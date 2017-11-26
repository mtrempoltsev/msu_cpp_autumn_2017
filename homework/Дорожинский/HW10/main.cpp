#include <iostream>
#include <thread>

std::mutex mutex;
std::condition_variable ping_ready;
std::condition_variable pong_ready;

bool is_ping_ready = true;
bool is_pong_ready = true;

void ping_thread() {
	static int counter = 10000;
	while (counter > 0) {
		{
			std::unique_lock<std::mutex> lock(mutex);
			while (!is_ping_ready) {
				ping_ready.wait(lock);
			}
			is_ping_ready = false;
			--counter;
			std::cout << "ping ";
			is_pong_ready = true;
		}
		pong_ready.notify_one();
	}
}

void pong_thread() {
	static int counter = 10000;
	while (counter > 0) {
		{
			std::unique_lock<std::mutex> lock(mutex);
			while (!is_pong_ready) {
				pong_ready.wait(lock);
			}
			is_pong_ready = false;
			--counter;
			std::cout << "pong ";
			is_ping_ready = true;
		}
		ping_ready.notify_one();
	}
}

int main(int argc, char const *argv[]) {
	std::thread pt1(ping_thread);
	std::thread pt2(pong_thread);
	pt1.join();
	pt2.join();
	return 0;
}