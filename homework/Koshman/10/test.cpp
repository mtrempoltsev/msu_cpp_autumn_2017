#include <sstream>

#include "ping_pong.h"

int errors = 0;


void test(std::vector<std::string> v, int iters)
{
	std::stringstream buffer;
	std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());
	
	ConcurentSuccessiveMessages Messages(v, iters);
	
	std::string loop = "";
	for (auto i: v)
	{
		for (auto j: i){
			loop += j;
		}
	}
	int ind = 0;
	int errors = 0;
	while (!Messages.is_finished())
		;
	std::cout.rdbuf(oldCoutStreamBuf);
	for (auto i: buffer.str())
	{
		if (i != loop[ind])
			errors++;
		ind = (ind + 1) % loop.size();
	}
}

int main(int argc, char const *argv[])
{
	std::vector<std::string> v;
	int iters;

	v.push_back("ping ");
	v.push_back("pong ");
	iters = 100 * 1000;
	test(v, iters);

	v.push_back("tree ");
	v.push_back("house ");
	iters = 1000 * 1000;
	test(v, iters);

	v.clear();
	v.push_back("If both base and exponent are zero, it may also cause a domain error on certain implementations. ");
	v.push_back("If the base is finite negative and the exponent is finite but not an integer value, it causes a domain error. ");
	v.push_back("short ");
	v.push_back("The result of raising base to the power exponent."
				"If the base is finite negative and the exponent is finite but not an integer value, it causes a domain error."
				"If both base and exponent are zero, it may also cause a domain error on certain implementations."
				"If base is zero and exponent is negative, it may cause a domain error or a pole error (or none, depending on the library implementation)."
				"The function may also cause a range error if the result is too great or too small to be represented by a value of the return type. ");
	iters = 1000 * 1000;

	std::cout << ((errors == 0) ? "Ok" : "Error");

	return 0;
}
