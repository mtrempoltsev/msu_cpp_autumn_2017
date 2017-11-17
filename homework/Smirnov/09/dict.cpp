#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

int main(int argc, char** argv)
{	

	char* file_name_in = argv[1];
	char* file_name_out = argv[2];
	std::unordered_map<std::string, int> dict;

	// Открытие файла для чтения
	std::ifstream file_in(file_name_in);
	if (!file_in)
	{
	    std::cout << "can't open file" ;
	    exit(1);
	}

	// Составление частотного словаря
	while (file_in.good())
	{
		std::string s;
		file_in >> s;
		if (dict.find(s) == dict.end())
		{	
			// Элемент впервые добавляется
			dict.insert(std::pair<std::string, int>(s, 1));
		}
		else
		{
			// Элемент уже есть
			dict[s]++;
		}
	}

	// Перевод словаря в вектор для сортировки по значениям
	std::vector<std::pair<std::string, int>> word_vec(dict.size());
	int i = 0;
	for(auto it = dict.begin(); it != dict.end(); it++)
	{	
		word_vec[i] = *it;
		++i;
	}

	// Сортировка
	std::sort(word_vec.begin(), word_vec.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b){return a.second > b.second;});

	// Открытие файла для записи
	std::ofstream file_out(file_name_out);
	if (!file_out)
	{
	    std::cout << "can't open file" ;
	    exit(1);
	}

	// Запись в файл результата
	for(auto it = word_vec.begin(); it != word_vec.end(); it++)
	{
		file_out << (*it).second << " " << (*it).first << std::endl;
	}

	return 0;
}