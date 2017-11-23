#include <iostream>
#include <map>
#include <cstring>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
	try{
		if(argc < 3){
			throw std::invalid_argument("Programm misses some arguments");
		}
		map<string,int> bagOfWords;
		std::ifstream file(argv[1]);
		if (!file)
		{
    		throw std::runtime_error("Input file error");
		}
		while (!file.eof())
		{
    		string s;
    		file >> s;
    		if(s == "") continue;
    		if(bagOfWords.find(s)!=bagOfWords.end()){
    			bagOfWords[s] += 1; 
    		}else bagOfWords[s] = 1;
		}

		multimap<int, string, std::greater<int>> bagOfFreqs;

		for(auto it = bagOfWords.begin(); it != bagOfWords.end(); ++it){
			bagOfFreqs.insert(std::make_pair((*it).second, (*it).first));
		}

		std::ofstream file_out(argv[2]);
		if (!file_out){
			throw std::runtime_error("Output file error");
		}

		for(auto it = bagOfFreqs.begin(); it != bagOfFreqs.end(); ++it){
			file_out << (*it).first << " " << (*it).second << endl;
		}
    	return 0;
	}catch(const std::invalid_argument& err){
		cout << err.what() << endl;
	}catch(const std::runtime_error& err){
		cout << err.what() << endl;
	}catch(...){
		cout << "Unexpected exception catched" << endl;
	}
}
