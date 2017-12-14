#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::fopen;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;
using std::lower_bound;
using std::stable_sort;

int
main(int argc, char ** argv)
{
	vector<pair<string, int>> vec;
	string str;
	if(argc != 3) {
		cout << "Error args" << endl;
		return 0;
	}
	ifstream file_in(argv[1]);
	if(!file_in.is_open()) {
		cout << "File in error" << endl;
		return 0;
	}
	while(file_in.good()) {
		str.clear();
		file_in >> str;
		if(str.empty()) {
			break;
		}
		auto iter = lower_bound(vec.begin(), vec.end(), str, [](const pair<string, int>& a, const string& str){return a.first < str;});
		if(iter == vec.end() || iter->first != str) {
			vec.insert(iter, make_pair(str, 1));
		} else {
			++iter->second;
		}
	}
	file_in.close();
	stable_sort(vec.begin(), vec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {return a.second > b.second;});
	ofstream file_out(argv[2]);
	if(!file_out.is_open()) {
		cout << "File out error" << endl;
		return 0;
	}
	for(auto iter: vec) {
		file_out << iter.second << " " << iter.first << endl;
	}
	file_out.close();
	return 0;
}
