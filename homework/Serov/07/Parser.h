#include <string>

using namespace std;

template <class T>
class Parser{
public:
	bool check(const string& in){
		return true;
	}
	
	double str_to_d(const string& in){
		return stod(in);
	}
};

template <>
class Parser<int>{
public:
	bool check(const string& in){
		if (in.find('.')!=string::npos)
			return false;
		else
			return true;
	}

	double str_to_d(const string& in){
		return stod(in);
	}
};

template <>
class Parser<long>{
public:
	bool check(const string& in){
		if (in.find('.')!=string::npos)
			return false;
		else
			return true;
	}

	double str_to_d(const string& in){
		return stod(in);
	}
};
