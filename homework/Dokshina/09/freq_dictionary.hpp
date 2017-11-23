#ifndef __FREQ_DICTIONARY_HPP
#define __FREQ_DICTIONARY_HPP

#include <fstream>
#include <string>
#include <exception>
#include <unordered_map>
#include <algorithm>


class FreqDictionary {
    typedef std::unordered_map <std::string, size_t>  MapDictionary;
    typedef std::vector<std::pair <std::string, size_t>> Dictionary;
    typedef std::pair<std::string, size_t> Word;
public:
    FreqDictionary(const char* input_file_name, const char* output_file_name);
    void make_dictionary();
    void sort_dictionary();
    void print_dictionary();

private:
    std::ifstream input_file;
    std::ofstream output_file;
    Dictionary freq_dictionary;

};

#endif
