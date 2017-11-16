#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <map>
#include <functional>
#include <vector>

void printError(int line = -1) 
{
    std::cerr << "Erro: " << line << std::endl;
}

int main(int argc, char* argv[]) 
{
    using pair = std::pair<std::string, int>;
    if (argc != 3) 
    {
        printError(__LINE__);
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in.good()) 
    {
        printError(__LINE__);
        return 1;
    }
    std::string s;
    std::map<std::string, int> dict;
    auto countWords = [&](const std::string& word) { dict[word]++; };
    std::for_each(std::istream_iterator<std::string>(in), 
                std::istream_iterator<std::string>(), countWords);
    std::vector<pair> vecCountDict;
    std::copy(dict.begin(), dict.end(), std::back_inserter(vecCountDict));
    auto cmp = [](const pair& x, const pair& y) 
    { 
        if (x.second == y.second) 
            return x.first < y.first; 
        else return x.second > y.second; 
    };
    std::sort(vecCountDict.begin(), vecCountDict.end(), cmp);
    std::ofstream out(argv[2]);
    if (!out.good()) 
    {
        printError(__LINE__);
        return 1;
    }
    auto print = [&](const pair& p) { out << p.second << " " << p.first << "\n"; };
    std::for_each(vecCountDict.begin(), vecCountDict.end(), print);
    return 0;
}