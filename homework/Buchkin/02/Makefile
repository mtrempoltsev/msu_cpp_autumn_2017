all: calc

calc: main.o parser.o
	g++ -std=c++14 -o calc main.o parser.o

main.o: main.cpp
	g++ -std=c++14 -o main.o -c main.cpp

parser.o: parser.cpp
	g++ -std=c++14 -o parser.o -c parser.cpp

clean:
	rm *.o
