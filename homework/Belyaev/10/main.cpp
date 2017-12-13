#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m;
std::condition_variable first_thread;
std::condition_variable second_thread;
bool first_notified = false;
bool second_notified = false;

void ping(){
	while(true){
        	std::unique_lock<std::mutex> lock(m);
		cout << "ping" << endl;
		second_thread.notify_one();
		first_notified = false;
		second_notified = true;
		while(!first_notified){
			first_thread.wait(lock);
		}
	}
}

void pong(){
	while(true){
        	std::unique_lock<std::mutex> lock(m);
		cout << "pong" << endl;
		first_notified = true;
		second_notified = false;
		first_thread.notify_one();
		while(!second_notified){
			second_thread.wait(lock);
		}
	}
}

int main(){
	thread uno(ping);
	thread duo(pong);
	uno.join();
	return 0;
}
