CC      	= g++
CFLAGS  	= -Wall -Werror -pedantic -std=c++14 -O2

all: main.o
	$(CC) $(CFLAGS) *.o -o prog

main.o: clean
	$(CC) $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -rf *.o prog