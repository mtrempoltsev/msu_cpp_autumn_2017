TARGET = test
CC = g++
OPTIONS = -std=c++11 -O2 -Wall

all: $(TARGET)

$(TARGET): test.o matrix.o
	$(CC) $(OPTIONS) -o $(TARGET) matrix.o test.o

test.o: test.cpp
	$(CC) $(OPTIONS) -c -o test.o test.cpp

matrix.o: matrix.cpp
	$(CC) $(OPTIONS) -c -o matrix.o matrix.cpp


clean:
	rm -rf $(TARGET) *.o
