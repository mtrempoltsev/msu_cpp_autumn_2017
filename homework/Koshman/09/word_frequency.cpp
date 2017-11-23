#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


int main(int argc, char const *argv[])
{
	std::ifstream file_in(argv[1]);
	std::ofstream file_out(argv[2]);
	std::vector<std::pair<std::string, int>> word_pairs;
	std::string line;

	// creating the word_pairs list of word -- frequency pairs
	while (std::getline(file_in, line))
	{	
		std::string word = "";
		for (char c : line += ' ') {
			if ((c == ' ') && (word != "")) {
				auto it = std::find_if(word_pairs.begin(), word_pairs.end(),
				    [word](const std::pair<std::string, int>& element){ return element.first == word;} );
				if (it == word_pairs.end()){
					std::pair<std::string, int> pair(word, 1);
					word_pairs.push_back(pair);
				} else {
					(*it).second++;
				}
			    word = "";
			} else {
				word += c;
			}
		}
	}
	
	// sorting the list by frequency, then by lexicographical order
	std::sort(word_pairs.begin(), word_pairs.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b) {
        if (a.second != b.second)
        	return a.second > b.second;   
        else 
        	return std::lexicographical_compare(a.first.begin(), a.first.end(), b.first.begin(), b.first.end());
    });
    
    for (auto pair: word_pairs){
    	file_out << pair.second << ' ' << pair.first << '\n';
    }
		
	return 0;
}
