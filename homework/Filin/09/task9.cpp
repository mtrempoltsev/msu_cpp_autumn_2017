//
//  main.cpp
//  Task9
//
//  Created by Максим on 19.11.17.
//  Copyright © 2017 Максим. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>



bool pred(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
{
    return a.second > b.second;
}


void count_words(std::string input_name, std::string output_name) {
    std::ifstream input_file;
    std::ofstream output_file;
    std::string word;
    std::map<std::string, int> words;
    
    input_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        input_file.open(input_name);
        
        while (!input_file.eof()) {
            input_file >> word;
            auto it = words.find(word);
            if (it == words.end()) {
                words[word] = 1;
            }
            else {
                it->second++;
            }
        }
        input_file.close();
    }
    catch (const std::ifstream::failure& e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
        
    //создаем вектор из map'a
    std::vector<std::pair<std::string, int> > vec(words.begin(), words.end());
    //сортируем этот вектор по значению
    std::sort(vec.begin(), vec.end(), pred);
    
    output_file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    try {
        output_file.open(output_name);
        for (int i = 0; i < vec.size(); i++) {
            output_file << vec[i].second << " " << vec[i].first << std::endl;
        }
        output_file.close();
    }
    catch (const std::ofstream::failure& e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    
    
}

int main(int argc, const char * argv[]) {
    
    std::string input_name;
    std::string output_name;
    
    try {
        switch(argc) {
            case 1: case 2:
                throw std::runtime_error("Not enough parameters");
                break;
            case 3:
                
              
                input_name = argv[1];
                output_name = argv[2];

                count_words(input_name, output_name);

                break;
            default:
                throw std::runtime_error("To many parameters");
                break;
        }
    }
    catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unexpected Exception" << std::endl;
    }
    return 0;
}
