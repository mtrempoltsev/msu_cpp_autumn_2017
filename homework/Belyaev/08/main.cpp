#include <iostream>
#include <unordered_map>
#include <cstring>
#include <limits>
#include <cmath>
#include <cfloat>
#include <memory>
#include "vector.h"

void shout_error(bool not_error)
{
	if(!not_error)
		cout << "error!" << endl;
}
void ch_push_back_pop_back() { //Also checks []
		_vector<int> a;
		a.push_back(3);
		shout_error(a.size() == 1 && a[0] == 3);
		auto b = a.pop_back();
		shout_error(a.size() == 0 && b == 3);
}


void ch_empty(){
	_vector<double> a = {1,2,3,4};
	shout_error(!a.empty());
	_vector<double> b;
	shout_error(b.empty());
}


void ch_clear(){
		_vector<int> a = {1,2,3,4};
		shout_error(!a.empty());
		a.clear();
		shout_error(a.empty());
}

void ch_iterators(){ //Also checks ++, --, *iterator, a[iterator]
		_vector<long> a(15,1100);
		long long fw = 0;
		long long rv = 0;
		for(auto it1 = a.begin();it1 != a.end(); ++it1){
			fw += *it1;
		}
		for(auto it1 = a.rend();it1 != a.rbegin(); --it1){
			rv += a[it1];
		}
		shout_error(fw == 16500);
		shout_error(rv == 16500);
}

void ch_resize(){
	_vector<int> a(1027);
	a.resize(1028,105);
	shout_error(a[1026] == 0 && a[1027] == 105);
}



int main(int argc, char* argv[]) {
	try{
	ch_push_back_pop_back();
	ch_empty();
	ch_clear();
	ch_iterators();
	ch_resize();
	cout << "End of tests" << endl;
	}catch(...){
			cout << "Unexpected exceptions" << endl;
	}
  return 0;
}
