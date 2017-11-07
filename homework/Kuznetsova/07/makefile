all: calc test_calc
calc: main.cpp number_reader.h tokenizer.h parser.h
	g++ -std=c++11 -Wall -Werror -Wextra main.cpp -o calc  -O2
test_calc: tests.cpp number_reader.h tokenizer.h parser.h
	g++ -std=c++11 -Wall -Werror -Wextra tests.cpp -o test_calc  -O2
clean:
	rm -rf *.o calc test_calc
