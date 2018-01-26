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
	// ПС, который может использоваться для защиты разделяемых данных от одновременного доступа нескольких потоков.
	// чтобы не ломиться в ресурс, который можно использовать только в одиночку
	
	// Вызывающий поток владеет мьютексом со времени успешного вызова lock или try_lock, и до момента вызова unlock.
	// Пока поток владеет мьютексом, все остальные потоки при попытке завладения им блокируются на вызове lock 
	// или получают значение false при вызове try_lock.
	std::mutex m;
	// ПС, который может быть использован для блокирования потока или нескольких потоков одновременно, пока не произойдет любое из событий.
	// чтобы поток дождался условия
	std::condition_variable cv;
	// можно добавить peng & другие состояния
	enum state 
	{ 
		ping, 
		pong 
	} curstate = ping;
	
	auto proc = [&m, &cv, &curstate](const char* msg, enum state mystate, enum state otherstate) {
		
		for(;;) 
		{
			// Любой поток, который намерен ждать на std::condition_variable должен сначала приобрести std::unique_lock. 
			// Операция ожидания атомарно освобождает мьютекс и приостанавливает выполнение потока. 
			// Когда переменная условия уведомляется, поток пробуждается, и мьютекс снова приобретается.
			std::unique_lock<std::mutex> lk(m);
			// ждет, пока другой поток все сделает и разбудит/ wait until notified
			// Параметры: 1. A unique_lock object whose mutex object is currently locked by this thread.
			// 2. A callable object or function that takes no arguments and returns a value that can be evaluated as a bool.
			// This is called repeatedly until it evaluates to true.
			cv.wait(lk, [&curstate, &mystate]{ return curstate == mystate; /* ожидаемое условие */});
			std::cout << msg << std::endl;
			curstate = otherstate;
			// all для случая, когда потоков > 2
			cv.notify_all();
#if 0
//#if _POSIX_VERSION >= 199309L
			// это позволяет проверять утечки с помощью valgrind
			if (terminate) return; 
#endif
		}
	};

	std::thread tping(proc, "ping", ping, pong), tpong(proc, "pong", pong, ping);
	// будит первый поток
	cv.notify_all();
	// ожидание завершения работы потоков
	tping.join();
	tpong.join();
	
	return 0;
}
