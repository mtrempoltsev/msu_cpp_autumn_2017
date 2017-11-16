#include <iostream>
#include <memory>
#include <stdexcept>

#include "myvector.hpp"
#include "myforwarditerator.hpp"
#include "myreverseiterator.hpp"

using namespace std;

int
main()
{
	Vector<int> a;
	for (int i = 0; i != 10; ++i) a.push_back(i + 5);
	
	for (int i = 0; i != 10; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
	
	for (Vector<int>::iterator it = a.begin(); it != a.end(); ++it) {
		cout << *it << " ";
	}
	
	cout << endl;
	
	for (Vector<int>::reverse_iterator it = a.rbegin(); it != a.rend(); it++) {
		cout << *it << " ";
	}
	
	cout << endl;
	
	auto it1 = a.begin();
	for (int i = 0; i != 3; i++, it1++);
	auto it2 = it1++;
	
	swap(*it1, *it2);
	
	for (it1 = a.begin(); it1 != a.end(); it1++) {
		cout << *it1 << " ";
	}
	cout << endl;
	
	for (auto it = a.rbegin(); it != a.rend(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	
	it1 = a.end();
	
	try {
		*it1;
	}
	catch (const std::runtime_error& exception) {
		cout << exception.what() << endl;
	}
	
	try {
		*a.rend();
	}
	catch (const std::runtime_error& exception) {
		cout << exception.what() << endl;
	}
	
	a.clear();
	
	try {
		a.pop_back();
	}
	catch (const std::runtime_error& exception) {
		cout << exception.what() << endl;
	}
	
	cout << endl;
	return 0;
}
