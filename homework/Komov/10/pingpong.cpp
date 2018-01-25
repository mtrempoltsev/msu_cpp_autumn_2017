#if 0
// this is only needed for correct termination by ctrl+C
//#ifdef __unix__
	#define _POSIX_C_SOURCE 200809L
	#include <unistd.h>
	#if _POSIX_VERSION >= 199309L // this is more strict than asking for sigaction() only
		#include <signal.h>
		static sig_atomic_t terminate = 0;
		static void handler(int) {
			terminate = 1;
		}
	#endif
#endif

#include <thread>
#include <mutex>
#include <iostream> // cout, endl
#include <condition_variable>

int main() {
#if 0
//#if _POSIX_VERSION >= 199309L
	struct sigaction sa = {}; // zero-initialize
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask); // just in case
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
#endif
	std::mutex m;
	std::condition_variable cv;
	// можно добавить peng & другие состояния
	enum state { ping, pong } curstate = ping;
	auto proc = [&m, &cv, &curstate](const char* msg, enum state mystate, enum state otherstate) {
		
		for(;;) {
			// parameter is the type of the mutex to lock.
			std::unique_lock<std::mutex> lk(m);
			// ждет, пока другой поток все сделает и разбудит
			cv.wait(lk, [&curstate, &mystate]{ return curstate == mystate; });
			std::cout << msg << std::endl;
			curstate = otherstate;
			// all для случая, когда потоков > 2
			cv.notify_all();
#if 0
//#if _POSIX_VERSION >= 199309L
			if (terminate) return; // this makes it possible to check for leaks with valgrind
#endif
		}
	};

	std::thread tping(proc, "ping", ping, pong), tpong(proc, "pong", pong, ping);
	// будит первый поток
	cv.notify_all();
	// ожидание завершения потоков
	tping.join();
	tpong.join();
	
	return 0;
}
