CC      	= g++
CFLAGS  	= -Wall -Werror -pedantic -std=c++11 -O2

all: matrix.o 
	$(CC) $(CFLAGS) -c main.cpp -o main.o
	$(CC) $(CFLAGS) *.o -o prog

matrix.o: clean
	$(CC) $(CFLAGS) -c matrix.cpp -o $@

clean:
	rm -rf *.o prog