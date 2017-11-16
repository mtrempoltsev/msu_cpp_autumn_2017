#define _SCL_SECURE_NO_WARNINGS
using namespace std;

#include <iostream>
#include "vector.cpp"
#include <string>


int main()
{
	cout << "Hello!" << endl;

	try
	{
		
		Vector<int> A = { 1,2,3,4,5,6,7,8 };
		A.print();

		A.resize(10,-17);
		A.print();

		A.clear();
		A.print();

		A.resize(5);
		A[4] = 4;
		A.at(3) = 3;
		A.print();

		Vector<int> B = {8,9,10,11};

		for(auto it = B.rbegin(); it != B.rend(); it++)
		{
			*it *= -1;
		}
		B.print();

		Vector<double> C = {};
		C.resize(15, 1.0);
		for (auto it = C.begin(); it != C.end(); it=it+3)
		{
			*it = 7;
		}
		C.print();
	}

	catch (const runtime_error& e)
	{
			cout << "error" << endl;
	}
	return 0;
}
