#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

void read_from_file_to_dictionary(std::ifstream& fin,
                                  std::map<std::string, int>& dictionary);
void sort_vector_by_frequency(std::vector<std::pair<std::string, int>>& vector);
void write_vector(std::vector<std::pair<std::string, int>>& vector,
                  std::ofstream& fout);
void print_dictionary(std::map<std::string, int>& dictionary);

int main(int argc, char* argv[]) {
    try {
        std::ostringstream msg;
        msg << "Incorrect arguments. Usage: " << argv[0]
            << " input.txt output.txt";
        if (argc < 3) {
            throw(std::invalid_argument(msg.str()));
        }

        std::ifstream fin(argv[1]);
        if (!fin) {
            throw(std::invalid_argument("Can't open input file"));
        }

        std::map<std::string, int> dictionary;
        read_from_file_to_dictionary(fin, dictionary);

        std::vector<std::pair<std::string, int>> vector;
        copy(dictionary.begin(), dictionary.end(), back_inserter(vector));

        sort_vector_by_frequency(vector);

        std::ofstream fout(argv[2]);
        if (!fout) {
            throw(std::invalid_argument("Can't open output file"));
        }

        write_vector(vector, fout);
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

void read_from_file_to_dictionary(std::ifstream& fin,
                                  std::map<std::string, int>& dictionary) {
    while (fin.good()) {
        std::string word;
        fin >> word;
        auto it = dictionary.find(word);
        if (it == dictionary.end()) {
            if (word.find_first_not_of(' ') != std::string::npos)
                dictionary.insert(std::pair<std::string, int>(word, 1));
        } else {
            it->second++;
        }
    }
}

void write_vector(std::vector<std::pair<std::string, int>>& vector,
                  std::ofstream& fout) {
    for (auto it = vector.begin(); it != vector.end(); ++it)
        fout << (*it).first << " " << (*it).second << std::endl;
}

void sort_vector_by_frequency(
    std::vector<std::pair<std::string, int>>& vector) {
    auto greater = [](std::pair<std::string, int> const& a,
                      std::pair<std::string, int> const& b) {
        return a.second != b.second
                   ? a.second > b.second
                   : a.first < b.first;  // words with same frequencies are
                                         // lexicographically ordered
    };
    std::sort(vector.begin(), vector.end(), greater);
}

void print_dictionary(std::map<std::string, int>& dictionary) {
    for (auto it = dictionary.begin(); it != dictionary.end(); ++it) {
        std::cout << (*it).first << " : " << (*it).second << std::endl;
    }
}
