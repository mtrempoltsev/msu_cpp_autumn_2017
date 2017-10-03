all: calc
calc: main.cpp calculator.cpp calculator.h
	g++ -Wall -Werror -Wextra main.cpp calculator.cpp -o calc -O2 -std=c++11
test: simple_tests.cpp calculator.cpp calculator.h
	g++ -Wall -Werror -Wextra simple_tests.cpp calculator.cpp -o test_calc -O2 -std=c++11
clean:
	rm -rf *.o calc test_calc
