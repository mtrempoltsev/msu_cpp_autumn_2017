//
//  main.cpp
//  thread
//
//  Created by Павел Адаменко on 12/14/17.
//  Copyright © 2017 Павел Адаменко. All rights reserved.
//

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex_ping;
std::mutex mutex_pong;
int iteration = 0;
int iteration_max = -1;

void thread_ping(){
    while(iteration < iteration_max || iteration_max == -1){
        //increase iteration if not inf loop
        if (iteration_max != -1)
            iteration += 1;
        //lock ping, lock pong
        mutex_ping.lock();
        std::cout << "ping ";
        //Continue 2 thread
        //lock ping, ulock pong
        mutex_pong.unlock();
    }
    mutex_ping.unlock();
    mutex_pong.unlock();
    std :: cout << "12";
    return;
}

void thread_pong(){
    while(iteration < iteration_max || iteration_max == -1){
        //lock ping, lock pong
        mutex_pong.lock();
        std::cout << "pong ";
        //unlock ping, lock pong
        mutex_ping.unlock();
    }
    return;
}

int main(int argc, const char * argv[]){
    iteration_max = -1;
    if(argc > 1)
    {
        iteration_max = atoi(argv[1]);
        if(iteration_max < -1)
            iteration_max = -1;
    }
    
    mutex_ping.unlock();
    mutex_pong.lock();
    
    std::thread t1(thread_ping);   //First thread
    std::thread t2(thread_pong);   //Second thread
    
    //Wait for 1 thread
    t1.join();
    //t1.terminate()//detach();
    return 0;
}