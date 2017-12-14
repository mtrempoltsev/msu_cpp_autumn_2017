CC = g++
CFLAGS = -std=c++14 -O2 -Wall -Werror -pthread

all:
	$(CC) $(CFLAGS) thread/thread/main.cpp -o main.o
	./thread/thread/main.o

compile:
	$(CC) $(CFLAGS) thread/thread/main.cpp -o main.o
run:
	./thread/thread/main.o
clean:
	rm thread/thread/main.o
