#include <atomic>
#include <csignal>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex ready[2];
std::atomic<bool> quit(false);

void
pingpong(std::string message, bool current) {
  try {
    while (true) {
      ready[current].lock(); // Lock own mutex

      std::cout << message << " ";
      std::cout.flush();

      if (quit) { // Catch ^C
        ready[!current].unlock(); // Unlock other mutex and exit
        return;
      } else {
        ready[!current].unlock(); // Unlock other mutex and resume
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

    std::thread t1(pingpong, "ping", 0);
    std::thread t2(pingpong, "pong", 1);

    ready[0].unlock();

    t1.join(); // Wait for ^C
    t2.join();

    return 0;
  } catch (...) {
    return 1;
  }
}
