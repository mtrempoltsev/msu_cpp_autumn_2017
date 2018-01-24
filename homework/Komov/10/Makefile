.PHONY: test
all: pingpong words

CXXFLAGS += --std=c++14 -g -Wall -Wextra -Wpedantic -fmax-errors=1 -pthread

test: pingpong words
	timeout --preserve-status -s INT 2 valgrind ./pingpong
	valgrind ./words wordsoup.txt sorted.txt
