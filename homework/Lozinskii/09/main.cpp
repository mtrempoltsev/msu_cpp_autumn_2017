#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <vector>
#include <iterator>
int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " file1 file2" <<std::endl;
    }
    
    std::map<std::string, unsigned int> dict;
    std::ifstream fin;
    std::ofstream fout;
    try {
        fin.open(argv[1]);
        fout.open(argv[2]);
    } catch (std::ios_base::failure e) {
        std::cout << "Can't open files" << std::endl;
    }

    if (!fin || !fout)
        std::cout << "Can't open files" << std::endl;

    std::string word;
    while(fin >> word) {
        if (dict.find(word) == dict.end()) 
            dict[word] = 1;
        else 
            ++dict[word];
    }

    auto cmp = [](std::pair<std::string,unsigned int> const & a, std::pair<std::string,unsigned int> const & b) 
    { 
        return a.second != b.second?  a.second < b.second : a.first < b.first;
    };
    
    std::vector<std::pair<std::string, unsigned>> vwords;
    std::copy(dict.begin(), dict.end(), std::back_inserter(vwords));
    std::sort(vwords.begin(), vwords.end(), cmp);
    auto write = [&fout](std::pair<std::string, unsigned int> a) {fout << a.second << " " << a.first << std::endl;};
    std::for_each(vwords.rbegin(), vwords.rend(), write);
    fin.close();
    fout.close();
    return 0;
}
