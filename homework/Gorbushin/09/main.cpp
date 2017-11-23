#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

int main(int argc, char **argv) {

    // Входные данные
    std::ifstream input_file(argv[1]);
    std::ofstream output_file(argv[2]);
    if (!input_file) {
        std::cerr << "Can not open input file: " << argv[1] << std::endl;
        return 1;
    }
    if (!output_file) {
        std::cerr << "Can not open output file: " << argv[2] << std::endl;
        return 1;
    }
    
    // Создание частного словаря
    std::map<std::string, int> frequency;
    while (input_file.good()) {
        std::string s;
        input_file >> s;
        if (s != "") {
            if (frequency.find(s) == frequency.end()) {
                frequency[s] = 1;
            } else {
                ++frequency[s];
            }
        }
    }

    // Создаем вектор из <частота, номер_слова>
    std::vector< std::pair<int, std::string> > back_frequency;
    back_frequency.reserve(frequency.size());
    for (auto &i : frequency) {
        back_frequency.push_back( std::make_pair(i.second, i.first) );
    }
    
    // Сортируем по частоте
    std::sort(back_frequency.begin(), back_frequency.end(), 
        [](const std::pair<int, std::string> &a, const std::pair<int, std::string> &b) { 
            return a.first > b.first;
        }
    );
    
    // Выводим ответ
    for (auto &i : back_frequency) {
        output_file << i.first << " " << i.second << std::endl;
    }

    return 0;
}
