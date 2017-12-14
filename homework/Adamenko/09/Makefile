CC = g++
CFLAGS = -std=c++14 -O2 -Wall -Werror

all:
	$(CC) $(CFLAGS) make_dict.cpp -o make_dict.o
	./make_dict.o in.txt out.txt
	head out.txt

compile:
	$(CC) $(CFLAGS) make_dict.cpp -o make_dict.o
run:
	./make_dict.o in.txt out.txt
clean:
	rm make_dict.o