#include <atomic>
#include <csignal>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex ready[2];
std::atomic<bool> quit(false);

void
ping(std::string message, bool current) {
  try {
    while (true) {
      ready[current].lock();

      std::cout << message << " ";
      std::cout.flush();

      if (quit) { // Catch ^C
        ready[!current].unlock();
        return;
      } else {
        ready[!current].unlock();
      }

    }
  } catch (...) {
    return;
  }
}

void
sigint(int) { // Handler
  quit = true;
}

int
main(int argc, char **argv)
{
  try {
    signal(SIGINT, sigint);

    ready[0].lock();
    ready[1].lock();

    std::thread t1(ping, "ping", 0);
    std::thread t2(ping, "pong", 1);

    ready[0].unlock();

    t1.join();
    t2.join();

    return 0;
  } catch (...) {
    return 1;
  }
}
