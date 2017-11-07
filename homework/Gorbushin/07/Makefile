TARGET = test
CC = g++
OPTIONS = -std=c++11 -O2 -Wall -g

all: $(TARGET)

$(TARGET): main.o Expression.o
	$(CC) $(OPTIONS) -o $(TARGET) Expression.o main.o

main.o: main.cpp
	$(CC) $(OPTIONS) -c -o main.o main.cpp

Expression.o: Expression.cpp
	$(CC) $(OPTIONS) -c -o Expression.o Expression.cpp


clean:
	rm -rf $(TARGET) *.o
