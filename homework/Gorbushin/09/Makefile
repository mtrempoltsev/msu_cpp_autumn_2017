TARGET = all
CC = g++
OPTIONS = -std=c++11 -O2 -Wall -g


all: count make_test test_checker

count: main.cpp
	$(CC) $(OPTIONS) -o count main.cpp

make_test: test_maker.cpp
	$(CC) $(OPTIONS) -o make_test test_maker.cpp 

test_checker: test_checker.cpp
	$(CC) $(OPTIONS) -o test_checker test_checker.cpp

clean:
	rm -rf input_test output output_test make_test test_checker count
