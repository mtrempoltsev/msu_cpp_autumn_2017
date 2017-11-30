#include <iostream>
#include <thread>
#include <mutex>


enum order
{
	ping,
	pong
};

std::mutex m;
int turn;


void print_ping()
{
	while (true)
	{
		std::lock_guard<std::mutex> lock(m);
		if (turn == order::ping)
		{
			std::cout << "ping" << ' ';
			turn = order::pong;
		}
	}
}


void print_pong()
{
	while (true)
	{
		std::lock_guard<std::mutex> lock(m);
		if (turn == order::pong)
		{
			std::cout << "pong" << ' ';
			turn = order::ping;
		}
	}
}


void start_ping_pong_game()
{
	std::thread t_ping(print_ping);
	std::thread t_pong(print_pong);
	t_ping.join();
	t_pong.join();
}
int main()
{
	start_ping_pong_game();
	return 0;
}