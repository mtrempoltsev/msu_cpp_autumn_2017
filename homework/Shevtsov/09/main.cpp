#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

void GeneralAlgorithm(const int argc, const std::string argv_1, const std::string argv_2){
	
	// проверим число аргументов 
	if (argc != 3) throw "Bad count of arguments";
	
	// задаем input
	std::ifstream in_file(argv_1); 
	if (!in_file) throw "can't open input file ";

	// задаем output
	std::ofstream out_file(argv_2); 
	if (!out_file) throw "can't open output file";

	// составим словарь состоящий из слов из input, где
	// ключи - слова, значения - число вхождений этого слова в input
	std::map <std::string, int> DictionaryMap;
	while (in_file.good())
	{
    		std::string s;
    		in_file >> s;
 		if (s == "") continue;  
		if (DictionaryMap.find(s) == DictionaryMap.end())
			DictionaryMap[s] = 1;
		else
			DictionaryMap[s]++;
	}

	// создадим вектор из пар (ключ, значения) содержащихся в словаре
	std::vector< std::pair<std::string,int> > VectorDictionaryMap;
	VectorDictionaryMap.reserve(DictionaryMap.size());
	for (auto it = DictionaryMap.begin() ; it != DictionaryMap.end(); ++it){
		VectorDictionaryMap.push_back( std::make_pair(it->first, it->second));
	}

	// отсортируем вектор пар по второму значению пары (по значению)
	auto condition = [](std::pair<std::string, int> &x,std::pair<std::string, int> &y){ 
		return x.second > y.second;
	};
	std::sort(VectorDictionaryMap.begin(), VectorDictionaryMap.end(), condition);

	// запишем отсортированный вектор в файл output
	for (auto it = VectorDictionaryMap.begin() ; it != VectorDictionaryMap.end(); ++it){
		out_file << it->second << " " << it->first << std::endl;
	}
}

int main(int argc, char *argv[]) {

	try {
		GeneralAlgorithm(argc, argv[1], argv[2]);	
	} 
	catch (const char* str){
    		std::cout << str << std::endl;
    		return 1;
  	}

	return 0;	
}
