#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

enum turn
{
	turn_ping,
	turn_pong
};

int counter;
mutex mut;

void ping(){
	while (true){
		lock_guard<mutex> lock(mut);
		if (counter == turn::turn_ping){
			cout << "ping ";
			counter = turn::turn_pong;
		}
	}
}

void pong(){
	while (true){
		lock_guard<mutex> lock(mut);
		if (counter == turn::turn_pong){
			cout << "pong ";
			counter= turn::turn_ping;
		}
	}
}

int main()
{
	thread thread_ping(ping);
	thread thread_pong(pong);
	thread_ping.join();
	thread_pong.join();
	return 0;
}
