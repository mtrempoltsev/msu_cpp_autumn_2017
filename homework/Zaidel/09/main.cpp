#include <iostream>
#include <map>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

class WordsCounter
{
public:
    WordsCounter(){}
    WordsCounter(std::string inputfile)
    {
        loadFromFile(inputfile);
    }

    void loadFromFile(std::string inputfile)
    {
        std::ifstream file(inputfile);
        if(!file)
        {
            throw std::runtime_error("Can not open file!");
        }

        while(file.good())
        {
            std::string word;
            file >> word;

            if(word.length() == 0)
            {
                continue;
            }

            if(freq_map.count(word) == 0)
            {
               freq_map[word] = 1;
            }
            else
            {
                freq_map[word]+=1;
            }
        }
    }

    void saveFrequences(std::string outputfile, bool save_sorted = false)
    {
        std::ofstream file_out(outputfile);
        if (!file_out){
            throw std::runtime_error("Can not open output file!");
        }

        std::vector<std::pair<std::string, int>> pairs;
        for (auto itr = freq_map.begin(); itr != freq_map.end(); ++itr)
            pairs.push_back(*itr);

        if(save_sorted) {
            std::sort(pairs.begin(), pairs.end(), [=](std::pair<std::string, int> &a, std::pair<std::string, int> &b) {
                          return a.second > b.second;
                      }
            );
        }

        for(auto pair : pairs)
        {
            file_out << pair.second << " " <<pair.first << std::endl;
        }

    }

private:
    std::map<std::string,int> freq_map;
};

int main(int argc, char* argv[])
{
    if(argc < 3){
        std::cout<< "Wrong arguments! Please try \"inputfile.txt outputfile.txt\" "<<std::endl ;
        return -1;
    }

    try {
        WordsCounter counter(argv[1]);
        counter.saveFrequences(argv[2], true);
        std::cout<<"OK"<< std::endl;
    }catch (std::exception& ex)
    {
        std::cout<< ex.what();
    }
}