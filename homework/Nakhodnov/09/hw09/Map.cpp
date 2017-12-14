//#include "stdafx.h"
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

template <typename _T1, typename _T2>
struct great_second
{
	typedef std::pair<_T1, _T2> type;
	bool 
	operator()(type A, type B) 
	{
		return A.second > B.second;
	}
};


int 
main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cerr << "Incorrect numbers of arguments" << std::endl;
		return 1;
	}
	std::ifstream ifile;
	std::ofstream ofile;
	try {
		ifile.open(argv[1], std::ios::in);
		ofile.open(argv[2], std::ios::trunc);
		if (!ifile.is_open()) {
			std::cerr << "Input file does not exist" << std::endl;
			return 1;
		}
	}
	catch (std::ios_base::failure& exeption) {
		std::cerr << exeption.what() << std::endl;
		return 1;
	}
	std::map<std::string, int> counter_dict;
	std::string buffer;
	while (ifile >> buffer) {
		++counter_dict[buffer];
	}
	std::vector <std::pair<std::string, int>> result(counter_dict.begin(), counter_dict.end());
	std::sort(result.begin(), result.end(), great_second<std::string, int>());
	for (auto x : result){
		ofile << x.second << ' ' << x.first << '\n';
	}
	return 0;
}