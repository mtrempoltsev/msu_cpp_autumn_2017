//
//  main.cpp
//  read_str
//
//  Created by Артем Кашипов on 13.12.17.
//  Copyright © 2017 Артем Кашипов. All rights reserved.
//

#include <iostream>
#include <string>
#include<fstream>
#include<unordered_map>
#include <map>
using namespace std;
int main(int argc, const char * argv[]) {
    if (argc <= 2){
        cout << "Pls give more arguments" << endl;
        return 0;
    }
    unordered_map<string, int> dict;
    string word,s;
    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cout << "can't open file" ;
        return 0;
    }
    
    while (file.good())
    {
        std::getline(file,s);
        for (int i=0; i<s.size(); i++){
            if (s[i]==' ' || i == (s.size()-1)){
                if (s[i]!=' '){
                    word.push_back(s[i]);
                }
                if (word[0]){
                    cout << word << endl;
                    if (!(dict.insert(make_tuple(word,1)).second)){
                        (dict.find(word)->second)++;;
                    }
                    word.clear();
                }
            }
            else {
                word.push_back(s[i]);
            }
        }
        
    }
    
    pair<int, string>* mass = new pair<int, string>[dict.size()];
    std::unordered_map<string, int>::iterator it;
    int i=0;
    for(it = dict.begin(); it!=dict.end(); it++){
        mass[i].second = it->first;
        mass[i].first = it->second;
        i++;
    }
    std::sort(mass,mass+dict.size());
    std::ofstream file_o(argv[2]);
    if (!file_o)
    {
        std::cout << "can't open file" ;
        return 0;
    }
    for (i =0 ; i< dict.size() ;i++){
        file_o << mass[i].first << " " << mass[i].second << endl;
    }
    delete[] mass;
    return 0;
}
