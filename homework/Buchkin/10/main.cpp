#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>


void threadFunction(std::mutex& mtx,
					std::condition_variable& cond, 
					bool& isPing,
					int outputNumber = 10,
					std::string str = std::string("ping"),
					bool wantedCondition = true)
{
	for (int i = 0; i < outputNumber; ++i) {
		std::unique_lock<std::mutex> lock(mtx);
		while (isPing != wantedCondition) {
			cond.wait(lock);
		}
		std::cout << str << std::endl;
		isPing = !isPing;
		cond.notify_all();
	}
}


void thr() {}

int
main()
{
	std::mutex mtx;
	std::condition_variable cond;
	bool isPing = true;
	
	std::thread t1(threadFunction, std::ref(mtx), std::ref(cond), std::ref(isPing), 10, "ping", true);
	std::thread t2(threadFunction, std::ref(mtx), std::ref(cond), std::ref(isPing), 10, "pong", false);
	
	t1.join();
	t2.join();

	return 0;
}
