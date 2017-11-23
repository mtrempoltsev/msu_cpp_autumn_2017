CC      	= g++
CFLAGS  	= -Wall -std=c++17 -O2 -pthread

all: clean
	$(CC) $(CFLAGS) main.cpp -o pingpong

clean:
	rm -rf *.o pingpong

tests: 
	./pingpong
