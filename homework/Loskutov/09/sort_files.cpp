#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdexcept>

void sortFiles(const std::string input, const std::string output) {
    std::map<std::string, std::size_t> map;
    std::ifstream input_file(input);
    
    if (!input_file)
        throw std::runtime_error("Could not open file!");
    while (input_file.good()) {
        std::string s;
        input_file >> s;
        ++map[s];
    }
    
    std::vector<std::pair<std::string, std::size_t>> v;
    auto make_tuple = [&v](std::pair<std::string, std::size_t> x) mutable { v.push_back(x); };
    auto conditions = [](std::pair<std::string, std::size_t> x, std::pair<std::string, std::size_t> y) { return x.second > y.second; };
    
    std::for_each(map.begin(), map.end(), make_tuple);
    std::sort(v.begin(), v.end(), conditions);
    
    std::ofstream output_file(output);
    if (!output_file)
        throw std::runtime_error("Could not create file!");
    
    for (auto it = v.begin(); it != v.end(); ++it)
        output_file << (*it).first << " " << (*it).second << std::endl;
}

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        std::cout << "Bad arguments! " << argv[1] << std::endl;
        return -1;
    }
    
    try {
        sortFiles(argv[1], argv[2]);
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}

