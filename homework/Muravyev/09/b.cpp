#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <fstream>

using namespace std;

int main(int argc, char** argv){
	string s;
	unordered_map<string, int> dict;    // Словарь слово-частота
	multimap<int, string> sorted_dict;  // Словарь частота-слово
	ifstream infile(argv[1]);
	if (!infile){       //  Открываем файлы
		cout << "Can't open input file" << endl;
		return 0;
	}
	ofstream outfile(argv[2]);
	if (!outfile){
		cout << "Can't open output file" << endl;
		return 0;
	}

	while(true){     // Читаем файл
		infile >> s;
		if (!infile.good()){
			break;
		}
		dict[s]++;  // Заполняем словарь
	}

	for (auto i : dict){  // Заполняем отсортированный по частоте словарь
		sorted_dict.insert(pair<int,string>(-i.second,i.first));
	}

	for (auto i : sorted_dict){ // Выводим результат в файл
		outfile << -i.first << " " << i.second << endl;
	}
	return 0;
}