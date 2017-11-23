#include <cstring>

#include "Library.h"

#define OPEN_WITH_POSSIBLE_EXCEPTION(file, name, flag) auto old_exc = file.exceptions();\
													   file.exceptions(std::ios::failbit);\
													   file.open(name, flag);\
													   file.exceptions(old_exc);

//========================================================================

map_type ParseFile(std::string file_name)
{
	map_type result;

	std::fstream file;
	OPEN_WITH_POSSIBLE_EXCEPTION(file, file_name, std::fstream::in);

	while (!file.eof())
	{
		std::string token;
		file >> token;
		if (token.empty()) { continue; }
		result[token]++;
	}

	//file.close(); Деструктор файла сам закроет его!

	return result;
}

std::vector<map_value_type> MapToVector(const map_type& map)
{
	return std::vector<map_value_type> (map.cbegin(), map.cend());
}

std::vector<map_value_type> GetMapValuesSorted(const map_type& map, bool increase)
{
	std::vector<map_value_type> result = MapToVector(map);
	std::sort(result.begin(), result.end(), [increase](const map_value_type& x, const map_value_type& y) -> bool
											{
												if (x.second != y.second) { return (!increase ^ (x.second < y.second)); }
												else
												{
													return x.first < y.first;
												}
											});
	return result;
}

std::string GenerateWord(size_t max_len)
{
	//В английском алфавите 26 букв
	const int alpbahet_length = 26;

	size_t word_len = rand() % max_len + 1;
	std::string result(word_len, '-');

	for (size_t i = 0; i < word_len; i++)
	{
		char base_char = (rand() % 2 == 0) ? 'A' : 'a';
		result[i] = base_char + (rand() % alpbahet_length);
	}

	return result;
}

map_type GetRandomMap(size_t count_words, size_t max_frequency, size_t max_len)
{
	map_type result;
	for (size_t i = 0; i < count_words; i++)
	{
		std::string new_word;
		do 
		{
			new_word = GenerateWord(max_len);
		} while (result [new_word] != 0); //Нужно сгенерировать слова, которого еще не было
		result[new_word] = rand() % max_frequency + 1;
	}

	return result;
}

void WriteFileFromMap(std::string file_name, const map_type& map)
{
	std::fstream file;
	OPEN_WITH_POSSIBLE_EXCEPTION(file, file_name, std::fstream::out);
	
	std::vector<map_value_type> elements = MapToVector(map);
	while (!elements.empty())
	{
		std::vector<map_value_type>::iterator next_element = elements.begin()+(rand() % elements.size());
		file << next_element->first << " ";
		--next_element->second;
		if (next_element->second == 0) { elements.erase(next_element); }
	}
}

void WriteVectorToFile(std::string file_name, const std::vector<map_value_type>& map)
{
	std::fstream file;
	OPEN_WITH_POSSIBLE_EXCEPTION(file, file_name, std::fstream::out);

	for (auto it = map.begin(); it != map.end(); ++it)
	{
		file << it->second << " " << it->first << std::endl;
	}
}