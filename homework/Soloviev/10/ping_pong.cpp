#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1;   //Mutex for 1 thread
std::mutex mutex2;   //Mutex for 2 thread

//Function for 1 thread
void threadFunc1(){
	while(1){
		//Stop 1 thread
		mutex1.lock();

		std::cout << "ping" << std::endl;
		
		//Continue 2 thread
		mutex2.unlock();
	}
}

//Function for 2 thread
void threadFunc2(){
	while(1){
		//Stop 2 thread
		mutex2.lock();
		
		std::cout << "pong" << std::endl;
		
		//Continue 1 thread
		mutex1.unlock();
	}
}

int main(){

	//Stop 2 thread, so that 1 thread can start first
	mutex2.lock();

	std::thread t1(threadFunc1);   //First thread
	std::thread t2(threadFunc2);   //Second thread

	//Wait for 1 thread
	t1.join();

	return 0;
}