all: prog

prog: main.o
	g++ -std=c++14 -o prog main.o -std=c++11

main.o: main.cpp
	g++ -std=c++14 -o main.o -c main.cpp -std=c++11

clean:
	rm *.o
	rm prog
