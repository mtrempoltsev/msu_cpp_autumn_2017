#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]){
	std::vector<std::string> words;                  //Vector of words from input file
	std::vector<std::pair<int, std::string>> dict;   //Vector of pairs: amount of occurrences, word

	std::ifstream ifile(argv[1]);                    //Input  file
	std::ofstream ofile(argv[2]);                    //Output file

	//Check if files can be opened
	if(!ifile || !ofile){
		std::cout << "can't open file" << std::endl;
		return -1;
	}

	//Read from input file into words vector
	while(ifile.good()){
		std::string s;
		ifile >> s;
		words.push_back(s);
	}

	ifile.close();

	//Last word is \n, so delete it
	words.pop_back();

	//Counting occurrences of words
	for(auto i = words.begin(); i != words.end(); ++i){
		if(std::find(words.begin(), i, *i) != i) continue;   //Check if the word hasn't been counted yet
		int n = std::count(words.begin(), words.end(), *i);  //Count occurrences
		dict.push_back(std::make_pair(n, *i));               //Add pait to the dict
	}

	//Sort dict, descending
	std::sort(dict.rbegin(), dict.rend());

	//Write dict to output file
	for(auto i = dict.begin(); i != dict.end(); ++i)
		ofile << (*i).first << " " << (*i).second << std::endl;

	ofile.close();

	return 0;
}