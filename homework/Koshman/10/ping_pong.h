#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>


struct ConcurentSuccessiveMessages
{
	ConcurentSuccessiveMessages(std::vector<std::string> messages, int iters=0) : 
	iters(iters),
	state(0),
	state_number(messages.size()),
	threads_finished(0)
	{
		int this_state = 0;
		for (auto message : messages)
		{
			std::thread t([=](){threadFunction(message, this_state);});
			threads.push_back(std::move(t));
			this_state++;
		}
	};

	void threadFunction(std::string message, int this_state)
	{
		int iter = 0;
		int max_iter = iters;
		while (!max_iter or (iter < max_iter)){
			if (state == this_state)
			{
				iter++;
			    std::unique_lock<std::mutex> lock(this_mutex);    
		    	std::cout << message;
			    state = (state + 1) % state_number;
			}
	    }
	    std::unique_lock<std::mutex> lock(this_mutex);
	    threads_finished++;
	}

	bool is_finished()
	{
		return threads_finished == state_number;
	};

	~ConcurentSuccessiveMessages()
	{
		for (auto &thread : threads)
		{
			thread.join();
		}
	};

private:
	int iters;
	int state;
	int state_number;
	int threads_finished;
	std::mutex this_mutex;
	std::vector<std::thread> threads;
};
