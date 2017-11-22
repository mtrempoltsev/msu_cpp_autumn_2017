#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;
using std::lower_bound;
using std::stable_sort;

int
main(int argc, char ** argv)
{
	if (argc != 3) {
		cout << "Wrong number of arguments; 2 needed" << endl;
		return 0;
	}
	
	ifstream input(argv[1]);
	if (!input.is_open()) {
		cout << "Cannot open input file" << endl;
		return 0;
	}
	
	vector<pair<string, int>> vec;
	string str;
	
	while (input.good()) {
		str.clear();
		input >> str;
		if (str.empty()) break;
		auto it = lower_bound(vec.begin(), vec.end(), str, 
		[](const pair<string, int>& a, const string& str){return a.first < str;});
		if (it == vec.end() || it->first != str) {
			vec.insert(it, make_pair(str, 1));
		} else {
			++it->second;
		}
	}
	
	input.close();
	
	stable_sort(vec.begin(), vec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {return a.second > b.second;});
	
	ofstream output(argv[2]);
	if (!output.is_open()) {
		cout << "Cannot open output file" << endl;
		return 0;
	}
	
	for (auto it: vec) {
		output << it.second << " " << it.first << endl;
	}
	
	output.close();
	
	return 0;
}
