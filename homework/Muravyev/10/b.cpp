#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

using namespace std;

bool p = true; // Переменная, указывающая, какое слово писать следующим
mutex m;

void ping(){
	while(true){
		if (p){
			m.lock();
			cout << "ping" << " ";
			fflush(stdout);  // Без этого в консоль ничего не писалось
			p = false;
			sleep(1);  // Спим, чтобы был красивый медленный вывод
			m.unlock();
		}
	}
}

void pong(){
	while(true){
		if (!p){
			m.lock();
			cout << "pong" << " ";
			fflush(stdout);  // Без этого в консоль ничего не писалось
			p = true;
			sleep(1);  // Спим, чтобы был красивый медленный вывод
			m.unlock();
		}
	}
}

int main(){
	thread t1(ping);
	thread t2(pong);
	t1.join();
	t2.join();
	return 0;
}