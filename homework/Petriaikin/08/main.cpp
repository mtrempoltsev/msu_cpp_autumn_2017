#include <utility>
#include <iostream>

#include "MyVector.hpp"

//==================================================================================================

template<typename T>
void PrintVector(MyVector<T> v, bool reverse = false)
{
	if (!reverse)
	{
		for (typename MyVector<T>::iterator curr = v.begin(); curr != v.end(); ++curr)
		{
			std::cout << *curr << " ";
		}
	}
	else
	{
		for (typename MyVector<T>::reverse_iterator curr = v.rbegin(); curr != v.rend(); ++curr)
		{
			std::cout << *curr << " ";
		}
	}

	std::cout << std::endl;
}

int main()
{
	MyVector<int> vect_int = { 1, 2, 3, 4, 5 };
	PrintVector(vect_int);
	PrintVector(vect_int, true);

	std::pair<int, int> def_pair = { 0, 1 };
	MyVector<std::pair<int, int>> vect_pairs(5, def_pair);

	std::pair<int, int> new_pair = vect_pairs[2];
	vect_pairs[2].second = 8;
	std::cout << vect_pairs[2].first << " " << vect_pairs[2].second << std::endl;

	vect_int.pop_back();
	PrintVector(vect_int);
	vect_int.push_back(7);
	PrintVector(vect_int);

	for (int i = 0; i < 100; i++)
	{
		vect_int.push_back(i*i);
	}
	PrintVector(vect_int);

	vect_int.resize(0);

	std::cout << vect_int.empty() << std::endl;
	try
	{
		int test = vect_int[0];
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	vect_int.push_back(11);
	PrintVector(vect_int);
}