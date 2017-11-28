#include <cstring>
#include "Library.h"

//========================================================================

#define ERROR_CODE 1

#define MAX_WORDS 500
#define WORDS_BASE 100 //Минимальное количество слов в файле
#define MAX_FREQUENCY 70
#define MAX_WORD_LEN 30

//========================================================================

void GenerateTests(int count = 10)
{
	std::string base_name = "test";
	std::string extension_test = ".in";
	std::string extension_check = ".chk";

	for (int i = 0; i < count; i++)
	{
		size_t words = WORDS_BASE + (rand() % (MAX_WORDS - WORDS_BASE));
		map_type test_map = GetRandomMap(words, MAX_FREQUENCY, MAX_WORD_LEN);
		WriteFileFromMap(base_name + std::to_string(i) + extension_test, test_map);
		WriteVectorToFile(base_name + std::to_string(i) + extension_check, GetMapValuesSorted(test_map));
	}
}

void ParseFile(std::string input_name, std::string output_name)
{
	WriteVectorToFile(output_name, GetMapValuesSorted(ParseFile(input_name)));
}

//========================================================================

int main(int count_args, char* args[])
{
	try
	{
		if (count_args < 2) { throw std::invalid_argument("Incorrect usage. --generate N for generating tests; <input_name> <output_name> for parsing"); }
		if (strcmp(args[1], "--generate") == 0)
		{
			int count_tests = 0;
			if (count_args > 2) { count_tests = atoi(args[2]); }
			if (count_tests <= 0)
			{
				std::cout << "Wrong count of tests. Please, specify positive integer. Will be used default number" << std::endl;
				GenerateTests();
			}
			else
			{
				GenerateTests(count_tests);
			}
		}
		else
		{
			if (count_args != 3) { throw std::invalid_argument("For parsing mode there should be 2 arguments: <input file name> <output file name>"); }
			ParseFile(args[1], args[2]);
		}
	}
	catch (std::exception& exc)
	{
		std::cout << "Error: " << exc.what();
		return ERROR_CODE;
	}
	catch (...)
	{
		std::cout << "Unknown error!";
		return ERROR_CODE;
	}
}