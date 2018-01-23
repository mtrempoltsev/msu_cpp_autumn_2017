.PHONY: test
all: hw4 hw5 hw8 vector test

CXXFLAGS += --std=c++14 -g -Wall -Wextra -Wpedantic -fmax-errors=1

test: hw4 hw5 vector
	valgrind ./hw4
	valgrind ./hw5
	valgrind ./vector
