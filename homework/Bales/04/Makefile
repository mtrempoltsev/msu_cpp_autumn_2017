CC      	= g++
CFLAGS  	= -Wall -Werror -pedantic -std=c++14 -O2

all: TMatrix.o 
	$(CC) $(CFLAGS) -c main.cpp -o main.o
	$(CC) $(CFLAGS) *.o -o prog

TMatrix.o: clean
	$(CC) $(CFLAGS) -c TMatrix.cpp -o $@

clean:
	rm -rf *.o prog