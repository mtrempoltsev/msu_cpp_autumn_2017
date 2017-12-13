TARGET = check
CC = g++
OPTIONS = -std=c++14 -O2 -Wall

all: $(TARGET)

$(TARGET): main.o calc.o
	$(CC) $(OPTIONS) -o $(TARGET) main.o calc.o

main.o: main.cpp
	$(CC) $(OPTIONS) -c -o main.o main.cpp

calc.o: calc.cpp
	$(CC) $(OPTIONS) -c -o calc.o calc.cpp

clean:
	rm -rf $(TARGET) *.o