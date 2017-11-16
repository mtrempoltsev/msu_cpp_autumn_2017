#include <iostream>
#include <vector>
#include "Tvector.h"
#include "Titerator.h"
using namespace std;
template<typename T>
void print(const Tvector<T>& vec) {
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

size_t test_num = 1;

inline void check(bool expr) {
	if (expr)
		cout << "#" << test_num << " success" << endl;
	else cout << "#" << test_num <<  " fail" << endl;
	++test_num;
}



int main() {
	try {
		
		Tvector<int> vec1;
		check(vec1.size() == 0);
		Tvector<int> vec2(5);
		check(vec2.size() == 5);
		Tvector<int> vec3(5, 0);
		check(vec3.size() == 5 && vec3.capacity() == 10 && vec3.data()[0] == 0 && vec3.data()[4] == 0);
		check(vec3[2] == 0);
		vec3.push_back(1);
		check(vec3.size() == 6 && vec3[5] == 1);
		vec3[0] = 1;
		check(vec3[0] == 1);
		vec3.pop_back();
		check(vec3.size() == 5 && vec3[4] == 0);
		vec3[5];
		cout << "fail" << endl;
	}
	catch (const char* msg) {
		cout << "#" << test_num <<  " success" << endl;
		++test_num;
	}
	catch (...) {
		cout << "fail" << endl;
	}
	try {
		Tvector<double> vec4(3, 0);
		check(vec4.capacity() == 6);
		vec4.push_back(1);
		vec4.push_back(1);
		vec4.push_back(1);
		check(vec4.size() == 6);
		vec4.push_back(1);
		check(vec4.size() == 7 && vec4.capacity() == 14 && vec4[6] == 1);
		Tvector<double> vec5 = vec4;
		check(vec4 == vec5);
	}
	catch (...) {
		cout << "fail" << endl;
	}
	try {
		Tvector<char> vec6(5, 'a');
		char test[] = { 'a', 'b', 'c', 'd', 'e' };
		vec6[1] = 'b';
		vec6[2] = 'c';
		vec6[3] = 'd';
		vec6[4] = 'e';
		int i = 0;
		for (auto iter = vec6.begin(); iter != vec6.end(); ++iter) {
			check(*iter == test[i]);
			++i;
		}
		i = 0;
		for (auto iter = vec6.rbegin(); iter != vec6.rend(); ++iter) {
			check(*iter == test[4 - i]);
			++i;
		}	
	}
	catch (...) {
		cout << "fail" << endl;
	}

	try {
		Tvector<int> vec7(2, 0);
		vec7.resize(4);
		check(vec7.size() == 4);
		vec7.resize(6, 1);
		check(vec7[0] == 0 && vec7.size() == 6 && vec7[5] == 1);
		vec7.clear();
		check(vec7.size() == 0);
		Tvector<int> vec8(3,0);
		vec8.resize(5,1);
		check(vec8[3] == 1 && vec8[4] == 1 && vec8[2] == 0);

	}
	catch (...) {
		cout << "fail" << endl;
	}
	
	return 0;
}
