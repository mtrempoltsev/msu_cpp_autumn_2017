all: calc

clean:
	rm -rf calc *.o

main.o: main.cpp
	g++ -std=c++14 -c -o main.o main.cpp -Werror

calc: main.o
	g++ -std=c++14 -o calc main.o
