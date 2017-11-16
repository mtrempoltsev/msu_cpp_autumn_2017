all: calc

calc: main.o
	g++ -std=c++14 -o calc main.o

main.o: main.cpp
	g++ -std=c++14 -o main.o -c main.cpp

clean:
	rm *.o
