CC      	= g++
CFLAGS  	= -Wall -pedantic -std=c++14 -O2

all: clean
	$(CC) $(CFLAGS) main.cpp -o freq-words
	./freq-words text.in text.out && cat text.out

clean:
	rm -rf *.o freq-words