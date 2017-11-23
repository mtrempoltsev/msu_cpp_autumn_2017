#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Invalid arguments!" << endl;
		return 1;
	}		
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	if (!fin) {
		cout << "File doesn't exist!" << endl;
		return 1;
	}

	vector<pair<string, int>> dictionary;	

	while (!fin.eof()) {
		string word;
		fin >> word;
		size_t i = 0;
		for (i = 0; i < dictionary.size(); ++i) {
			if (dictionary[i].first == word) {
				dictionary[i].second += 1;
				break;
			}
		}
		if (i == dictionary.size()) {
			dictionary.push_back(pair<string, int>(word, 1));
		}		
	}

	auto cmp = [](pair<string, int> const &a, pair<string, int> const &b) {
		return a.second != b.second ? a.second > b.second : a.first < b.first;
	};

	sort(dictionary.begin(), dictionary.end(), cmp);
	for (auto iter = dictionary.begin(); iter != dictionary.end(); ++iter) {
		fout << iter->first << "  " << iter->second << endl;
	}
	return 0;
}