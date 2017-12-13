#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1;
std::mutex mutex2;


void ping(){
	while(1){

		mutex1.lock();

                std::cout << "ping ";

		mutex2.unlock();
	}
}


void pong(){
	while(1){

		mutex2.lock();
		
                std::cout << "pong ";
		

		mutex1.unlock();
	}
}

int main(){


	mutex2.lock();

        std::thread t1(ping);
        std::thread t2(pong);


	t1.join();
        t2.join();
	return 0;
}
