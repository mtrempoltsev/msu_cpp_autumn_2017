#include <cassert> // assert
#include <fstream> // ifstream, ofstream
#include <unordered_map>
#include <map>
#include <string>
#include <cstddef> // size_t
#include <algorithm> // transform
#include <functional> // greater

int main(int argc, char** argv) 
{	
	assert(argc == 3);
	// считываем текст в unordered word->freq map
	// map сортирует по ключу
	std::unordered_map<std::string, std::size_t> freq;
	
	std::ifstream words(argv[1]);
	assert(words);

	while (words) {

		std::string word;
		// пропускаем пробельные символы, считываем до следующего пробела
		words >> word;
		// чтобы не было ошибки в конце файла
		if (word.size() != 0)
			freq[word]++;
	}

	// меняем unordered word->frequency map на отсортированную freq->word map
	// частоты, очевидно, не уникальны, поэтому multimap
	std::multimap<std::size_t, std::string, std::greater<std::size_t>> flipped;
	
	std::transform(
		freq.begin(), freq.end(),
		std::inserter(flipped, flipped.end()),
		[](const std::pair<std::string, std::size_t> & p) -> std::pair<std::size_t, std::string> {
			
			return {p.second, p.first};
		}
	);
	
	// вывод результата во второй файл
	std::ofstream res(argv[2]);
	assert(res);
	
	for (auto it = flipped.begin(); it != flipped.end(); it++)
	
		res << it->first << '\t' << it->second << std::endl;

	
	return 0;
}
