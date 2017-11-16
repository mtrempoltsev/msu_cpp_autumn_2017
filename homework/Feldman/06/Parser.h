#include <iostream>
#include <string>
using namespace std;
template <class T>
struct Parser {
	bool isCorrect(const string& src) { return true;  }
};

template<>
struct Parser<int> {
	bool isCorrect(const string& src) {
		if (src.find('.') != string::npos)
			return false;
		return true;
	}
	
};
template<>
struct Parser<long long int> {
	bool isCorrect(const string& src) {
		if (src.find('.') != string::npos)
			return false;
		return true;
	}

};