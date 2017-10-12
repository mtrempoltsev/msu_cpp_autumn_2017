#include<iostream>
#include "Calculator.h"

int main(int argc, char* argv[])
{
	if (argc < 2)
		std::cout << "A few argumtn" << std::endl;
	if (argc > 2)
		std::cout << "Too many argument" << std::endl;
	 
	Calculator c(argv[1]);
	try
	{
		std::cout << c.Calculate() << std::endl;
	}
	catch (std::string s)
	{
		std::cout << s << std::endl;
		return 1;
	}
	return 0;
}