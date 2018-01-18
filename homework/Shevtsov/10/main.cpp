#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex M;
std::condition_variable threadready;
// Условная переменная - позволяет блокировать один или более потоков,
// пока не произойдет некое определенное действие (например, уведомлние
// от другого потока)


// Идея:
// Ожидающий поток должен сначала выполнить unique_lock. Эта блокировка передается 
// методу wait(), который освобождает мьютекс и приостанавливает поток, пока не будет 
// получен сигнал от условной переменной. Когда это произойдет, поток пробудится и 
// снова выполнится lock.


// функция, которая будет выполняться в потоке
void thread(std::string game_command)
{
	while(1)
	{
		std::unique_lock<std::mutex> lock(M);
		std::cout << game_command << std::endl;
		threadready.notify_one(); // уведомление об истинности условия 
		threadready.wait(lock); // освобождение мьютекса
	}
}


int main(int argc, const char * argv[]) {

	// запуск потоков, двух игроков
	std::thread t1(thread, "ping");
	std::thread t2(thread, "pong");

	// синхронизация потоков
	t1.join();
	t2.join();	

	return 0;
}
