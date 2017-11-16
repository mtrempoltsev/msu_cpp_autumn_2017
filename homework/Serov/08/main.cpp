#include <iostream> 
#include "Tvector.h"

void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}

int main()
{
	try
	{
		Tvector<int> vec1(5);
		check(vec1[4] == 0);
		check(vec1.size() == 5);

		Tvector<double> vec2(5,1);
		check(vec2[1] == 1);
		check(vec1.size() == 5);

		vec2.resize(2);
		check(vec2.size() == 2);	
				
		vec2.resize(5);
		check(vec2.size() == 5);
		check(vec2[4] == 1);		

		vec2.push_back(2);
		check(vec2[5] == 2);
		check(vec2.size() == 6);
		
		vec2.pop_back();
		check(vec2.size() == 5);

		Tvector<int> vec3(10, 1);
		for (auto iter1 = vec3.begin(); iter1 != vec3.end(); ++iter1)		
			check(*iter1 == 1); 
		for (auto iter2 = vec3.rbegin(); iter2 != vec3.rend(); ++iter2)
			check(*iter2 == 1);
	}
	catch(const char* error_message)
	{
		std::cout << error_message << std::endl;
		return 1;
	}
	catch(...)
	{
		std::cerr << "Tests failed" << std::endl;
		return 2;
	}
	
	return 0;
}
