.PHONY: all clean

all: calc

clean:
			rm -rf hello *.o
calc.o: calc.c
			gcc -c -o calc.o calc.c
calc: calc.o
			gcc -o calc calc.o
