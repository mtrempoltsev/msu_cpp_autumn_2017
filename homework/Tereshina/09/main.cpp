#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>

class FrequencyDict {

    std::unordered_map<std::string, size_t> frequencyDictionary_;
    std::vector<std::pair<std::string, size_t>> words_;

    void read_words_(const char* path) {

        std::ifstream ifile(path);
            if (!ifile) {
                throw "Can't open input file";
            }
        std::string s;
        ifile >> s;
        
        while (!ifile.eof()) {
            ifile >> s;

            auto it = frequencyDictionary_.find(s);
            if (it == frequencyDictionary_.end()) {
                frequencyDictionary_[s] = 1;
            } else {
                it->second++;
            }
        }

        ifile.close();
    }

    void sort_frequencies_() {
        
        for(auto it : frequencyDictionary_) {
            words_.push_back(it);
        }

        std::sort(words_.begin(), 
                  words_.end(), 
                  [](std::pair<std::string, size_t> x, std::pair<std::string, size_t> y) 
                        {return x.second > y.second;}
                 );
    }

    void write_frequencies_(const char* path) {

        std::ofstream ofile(path);
        if (!ofile) {
            throw "Can't open output file";
        }

        for(auto it : words_) {
            ofile << it.second << ' ' << it.first << std::endl;
        }
        ofile.close();

    }

public:
    void make_frequency_dictionary(const char* inpath, const char* outpath) {

        read_words_(inpath);
        sort_frequencies_();
        write_frequencies_(outpath);
    }
};
int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            throw "Wrong number of arguments";
        }
        
        FrequencyDict().make_frequency_dictionary(argv[1], argv[2]);

    } catch (const char* expression) {
        std::cerr << expression << std::endl;
        return 1;
    }
    return 0;
}
