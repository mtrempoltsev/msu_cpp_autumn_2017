all: calc

clean:
	rm -rf calc *.o

main.o: main.cpp
	g++ -std=c++17 -c -o main.o main.cpp

calc: main.o
	g++ -std=c++17 -o calc main.o
