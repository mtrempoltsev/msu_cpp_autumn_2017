#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>

void read_words(const char* path, 
                std::unordered_map<std::string, size_t>& frequencyDictionary) {

    std::ifstream ifile(path);
        if (!ifile) {
            throw "Can't open input file";
        }
    std::string s;
    ifile >> s;
    
    while (!ifile.eof()) {
        ifile >> s;

        auto it = frequencyDictionary.find(s);
        if (it == frequencyDictionary.end()) {
            frequencyDictionary[s] = 1;
        } else {
            it->second++;
        }
    }

    ifile.close();
}

void sort_frequencies(std::unordered_map<std::string, size_t>& 
                                frequencyDictionary,
                      std::vector<std::pair<std::string, size_t>>& 
                                words) {
    
    for(auto it : frequencyDictionary) {
        words.push_back(it);
    }

    std::sort(words.begin(), 
              words.end(), 
              [](std::pair<std::string, size_t> x, std::pair<std::string, size_t> y) 
                    {return x.second > y.second;}
             );
}

void write_frequencies(const char* path, 
                       std::vector<std::pair<std::string, size_t>>& words) {

    std::ofstream ofile(path);
    if (!ofile) {
        throw "Can't open output file";
    }

    for(auto it : words) {
        ofile << it.second << ' ' << it.first << std::endl;
    }
    ofile.close();

}

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            throw "Wrong number of arguments";
        }
        
        std::unordered_map<std::string, size_t> frequencyDictionary;
        std::vector<std::pair<std::string, size_t>> words;
    
        read_words(argv[1], frequencyDictionary);

        sort_frequencies(frequencyDictionary, words);

        write_frequencies(argv[2], words);

    } catch (const char* expression) {
        std::cerr << expression << std::endl;
        return 1;
    }
    return 0;
}
