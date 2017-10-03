TARGET = eval
CC = g++
OPTIONS = -std=c++11 -O2 -Wall

all: eval

clean:
	rm -rf $(TARGET) *.o
main.o: main.cpp
	$(CC) $(OPTIONS) -c -o main.o main.cpp
$(TARGET): main.o
	$(CC) -o $(TARGET) main.o
