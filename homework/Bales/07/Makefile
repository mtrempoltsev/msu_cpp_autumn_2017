CC      	= g++
CFLAGS  	= -Wall -pedantic -std=c++14 -O2

all: TTokenizer.o
	$(CC) $(CFLAGS) -c main.cpp -o main.o
	$(CC) $(CFLAGS) *.o -o calc

TTokenizer.o: clean
	$(CC) $(CFLAGS) -c TTokenizer.cpp -o $@

clean:
	rm -rf *.o calc