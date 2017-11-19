#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <stdexcept>
#include <map>
#include <algorithm>

void parse(const char* fin, const char* fout){
    std::map<std::string, int> dict;
    std::ifstream file_in(fin);
    if (!file_in)
        throw std::invalid_argument("Error with open input file");
        
    while (file_in.good()){
        std::string s;
        file_in >> s;
        auto it = dict.find(s);
        if (it == dict.end())
            dict.insert(std::pair<std::string, int> (s, 1));
        else
            ++it->second;
    }
    
    std::vector<std::pair<std::string, int>> new_dict(dict.size());
    std::copy(dict.begin(), dict.end(), new_dict.begin());
    auto compare = [](const std::pair<std::string, int>& x,
                      const std::pair<std::string, int>& y){ return x.second > y.second;};
    std::sort(new_dict.begin(), new_dict.end(), compare);
    
    std::ofstream file_out(fout);
    if (!file_out)
        throw std::invalid_argument("Error with open output file");
    
    auto it = new_dict.begin();
    while (it != new_dict.end()){
        file_out << it->second << " " << it->first << "\n";
        ++it;
    }
}

int main(int argc, char** argv){
    try{
        if (argc == 1){
            char fin[] = "input.txt";
            char fout[] = "output.txt";
            parse(fin, fout);
            return 0;
        }
        parse(argv[1], argv[2]);
    }
    catch(std::invalid_argument& e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}