CXX = clang++
OPTIONS = -std=c++14 -O3 -Wpedantic -Wall -Wextra

.PHONY: test clean

all: calc
test: calc test.py
	python2 test.py
calc: calc.cpp parsing.cpp parsing_error.cpp
	$(CXX) -o $@ $< $(OPTIONS)
clean:
	rm -rf parse
