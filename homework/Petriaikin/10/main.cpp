#include <thread>
#include <iostream>
#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>

//========================================================================

#define COUNT_WORDS 10000

//========================================================================

enum class StateType
{
	PING,
	PONG
};

struct State
{
	StateType state_type;
	std::function<void()> called_function;
};

void ThreadWrapper(State& state_thread, StateType next_state, std::atomic<StateType>& current_state)
{
	int printed = 0;
	while (printed < COUNT_WORDS)
	{
		//Ожидаем, пока другой поток напечатает
		if (current_state == state_thread.state_type)
		{
			state_thread.called_function();
			printed++;
			atomic_exchange(&current_state, next_state);
		}
	}
}

int main()
{
	State ping = {StateType::PING, [] {std::cout << "ping "; }};
	State pong = {StateType::PONG, [] {std::cout << "pong "; }};
	std::atomic<StateType> current_state(StateType::PING);

	std::thread thread_ping(ThreadWrapper, std::ref(ping), StateType::PONG, std::ref(current_state));
	std::thread thread_pong(ThreadWrapper, std::ref(pong), StateType::PING, std::ref(current_state));

	thread_ping.join();
	thread_pong.join();

	return 0;
}