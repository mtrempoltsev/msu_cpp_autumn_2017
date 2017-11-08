CC = g++
CFLAGS = -std=c++14 -O2 -Wall -Wextra
TYPE = 
.PHONY: all clean

all:
	$(CC) $(CFLAGS) -D$(TYPE) -o calc CalculatorV5.cpp
	$(CC) $(CFLAGS) -o make_tests Tester.cpp
clean:
	rm -rf calc make_tests