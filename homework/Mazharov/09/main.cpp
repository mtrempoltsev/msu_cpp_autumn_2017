#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

bool cmp(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
    return a.second > b.second;
}

void count_words(std::string input, std::string output) {
    std::map<std::string, int> words;
    std::string word;
    std::ifstream input_file(input);
    std::ofstream output_file(output);

    if (!input_file or !output_file)
        throw std::runtime_error("Can't open file");

    while (!input_file.eof()) {
        input_file >> word;
        if (words.find(word) == words.end())
            words[word] = 1;
        else {
            words[word]++;
        }
    }
    input_file.close();

    std::vector<std::pair<std::string, int> > vec(words.begin(), words.end());
    std::sort(vec.begin(), vec.end(), cmp);

    for (int i = 0; i < vec.size(); i++) {
        output_file << vec[i].second << " " << vec[i].first << std::endl;
    }
    output_file.close();
}


int main(int argc, const char *argv[]) {
    try {
        if (argc < 3)
            throw std::runtime_error("Not enough parameters");
        else if (argc == 3) {
            std::string input_name;
            std::string output_name;

            std::cout << input_name << ' ' << output_name;
            input_name = argv[1];
            output_name = argv[2];

            count_words(input_name, output_name);
        } else
            throw std::runtime_error("To many parameters");
    }
    catch (const std::runtime_error &error) {
        std::cerr << error.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unexpected Exception" << std::endl;
    }
    return 0;
}

