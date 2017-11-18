#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <set>


typedef std::unordered_map <std::string, size_t>  Dictionary;
typedef std::vector<std::pair <std::string, size_t>> VectorDictionary;


Dictionary make_dictionary(const char* input_file_name) {
    std::string word;
    std::ifstream input_file(input_file_name);
    Dictionary dictionary;


    if (!input_file) {
        throw std::runtime_error("Cannot open file");
    }

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

    return dictionary;
}


VectorDictionary sort(Dictionary& dictionary) {
    VectorDictionary dict_vector(dictionary.begin(), dictionary.end());

    typedef std::pair<std::string, size_t> ValueType;
    std::sort(dict_vector.begin(), dict_vector.end(), [](const ValueType& x, const ValueType& y)
                                                        {return x.second > y.second;});
    return dict_vector;
}


void print_result(const char *output_file_name, const VectorDictionary& sorted_dict) {
    std::ofstream output_file(output_file_name);

    if (!output_file) {
        throw std::runtime_error("Cannot open file");
    }

    for (auto &elem : sorted_dict) {
        output_file << elem.second << ' ' << elem.first << std::endl;
    }
}


int main(int argc, char** argv) {
    try {
        if (argc != 3) {
            throw std::runtime_error("Invalid input! Please enter file names");
        }
        auto dictionary = std::move(make_dictionary(argv[1]));
        auto sorted_dict = sort(dictionary);
        print_result(argv[2], sorted_dict);

    } catch (std::exception& err) {
        std::cout << "Error: " << err.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Something wrong." << std::endl;
        return 1;
    }
    return 0;
}
