#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>


// Практическая часть

// Программе через аргументы командной строки передают два имени файлов. 
// Первое имя - текстовый файл в котором слова разделены пробелами, его надо прочесть, 
// составить частотный словарь "слово" - "сколько раз встречается". 
// После этого надо отсортировать словарь по частоте и вывести во второй файл (его имя - второй аргумент).

// Пример

// input.txt

// трава дерево лес трава
// output.txt

// 2 трава
// 1 дерево
// 1 лес
// 

int main(int argc, char** argv)
{   

    char* fileNameIn  = argv[1];
    char* fileNameOut = argv[2];
    std::unordered_map<std::string, int> dict;

    //Open file
    std::ifstream fileIn(fileNameIn);
    if (!fileIn)
    {
        std::cout << "[error] Can't open input file" ;
        return 1;
    }

    std::ofstream fileOut(fileNameOut);
    if (!fileOut)
    {
        std::cout << "[error] Can't open output file" ;
        return 1;
    }

    //Make freq dict
    while (not fileIn.eof())
    {
        std::string w;
        fileIn >> w;
        // std :: cout << w;
        //dict[w] +=1 if w in dict else dict[w] = 1
        if (dict.find(w) == dict.end())
        {   
            dict.insert(std::pair<std::string, int>(w, 1));
        }
        else
        {
            dict[w]++;
        }
    }

    //Sort
    // dict -> vector<pait<str, int>>
    std::vector<std::pair<std::string, int>> pairs(dict.size());
    int c = 0;
    for(auto sample = dict.begin(); sample != dict.end(); sample++)
    {   
        pairs[c] = *sample;
        ++c;
    }

    //https://stackoverflow.com/questions/20155220/how-to-sort-a-vectorpairstring-pairint-int
    std::sort(pairs.begin(), pairs.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b){return a.second > b.second;});

    //Write to end file
    for(auto sample = pairs.begin(); sample != pairs.end(); sample++)
    {
        fileOut << (*sample).second << " " << (*sample).first << "\n";
    }

    return 0;
}