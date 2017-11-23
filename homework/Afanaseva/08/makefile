CC      	= g++
CFLAGS  	= -Wall -std=c++14 -O2

all: clean
	$(CC) $(CFLAGS) iterator.h vector.h main.cpp -o run-tests

clean:
	rm -rf *.o run-tests

tests: 
	./run-tests
