#include <iostream>
#include <unordered_map>
#include <cstring>
#include <limits>
#include <cmath>
#include <cfloat> 
#include <memory>
#include "vector.h"





int main(int argc, char* argv[]) {
	_vector<int> a;
	a.push_back(3);
	_vector<int> b(5);
	_vector<int> c(5,6);
	_vector<int> d = {1,2,3,4};
	std::cout << d[3] << " " << c[2] << " " << b[1] << " " << a[0] << std::endl;
	std::cout << d.pop_back() << std::endl << d;
	auto z = d.begin();
	for(auto it1 = d.begin();it1 < d.end(); ++it1){
		std::cout << *it1 << " " << std::endl;
	}
	for(auto it1 = d.rbegin();it1 < d.rend(); ++it1){
		std::cout << *it1 << " " << std::endl;
	}
    return 0;
}
