#include "freq_dictionary.hpp"


FreqDictionary::FreqDictionary(const char* input_file_name, const char* output_file_name)
                : input_file(input_file_name)
                , output_file(output_file_name) {
    if (!input_file) {
        throw std::runtime_error("Cannot open input file");
    }

    if (!output_file) {
        throw std::runtime_error("Cannot open output file");
    }
}


void FreqDictionary::make_dictionary() {
    std::string word;
    MapDictionary dictionary;

    while (input_file.good()) {
        input_file >> word;
        if (input_file.eof()) {
            break;
        }

        if (dictionary.find(word) == dictionary.end()) {
            dictionary.insert({word , 1});
        } else {
            dictionary[word]++;
        }
    }
    freq_dictionary = Dictionary(dictionary.begin(), dictionary.end());
}


void FreqDictionary::sort_dictionary() {
    std::sort(freq_dictionary.begin(), freq_dictionary.end(), [](const Word& x, const Word& y)
                                                        {return x.second > y.second;});
}


void FreqDictionary::print_dictionary() {
    for (auto &elem : freq_dictionary) {
        output_file << elem.second << ' ' << elem.first << std::endl;
    }
}
