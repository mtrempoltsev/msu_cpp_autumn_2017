CC      	= g++
CFLAGS  	= -Wall -pedantic -std=c++14 -O2

all: TTokenizer.o
	$(CC) $(CFLAGS) -c main.cpp -o main.o
	$(CC) $(CFLAGS) *.o -o calc

TTokenizer.o: DefFunc.o
	$(CC) $(CFLAGS) -c TTokenizer.cpp -o $@

DefFunc.o: clean
	$(CC) $(CFLAGS) -c DefFunc.cpp -o $@

clean:
	rm -rf *.o calc