TARGET = test
CC = g++
OPTIONS = -std=c++11 -O2 -Wall -g

all: $(TARGET)

$(TARGET): main.o Vector.o
	$(CC) $(OPTIONS) -o $(TARGET) Vector.o main.o

main.o: main.cpp
	$(CC) $(OPTIONS) -c -o main.o main.cpp

Vector.o: Vector.cpp
	$(CC) $(OPTIONS) -c -o Vector.o Vector.cpp


clean:
	rm -rf $(TARGET) *.o
