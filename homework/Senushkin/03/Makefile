CC = g++
CFLAGS =-c -std=c++11 

all:
	$(CC) -o RDParser.o $(CFLAGS) RDParser.cpp
	$(CC) -o main.o $(CFLAGS) main.cpp
	$(CC) -o calc main.o RDParser.o
