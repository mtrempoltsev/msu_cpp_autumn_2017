CC      	= g++
CFLAGS  	= -Wall -std=c++14 -O2

all: clean
	$(CC) $(CFLAGS) main.cpp -o dict

clean:
	rm -rf *.o dict

tests: 
	./dict input.txt output.txt
