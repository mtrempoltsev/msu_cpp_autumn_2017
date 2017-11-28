#ifndef __PING_PONG
#define __PING_PONG

#include <iostream>
#include <thread>
#include <mutex>


enum Turn
{
    PING,
    PONG
};

void ping();
void pong();
void start_ping_pong_game();



#endif
