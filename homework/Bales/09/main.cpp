#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <map>
#include <functional>
#include <vector>

void printError(const std::string& s = "", int line = -1) 
{
    std::cerr << "Erro: " << s << " [:" << line << "]\n";
}

int main(int argc, char* argv[]) 
{
    using pair = std::pair<std::string, int>;
    if (argc != 3)
    {
        printError("number of params is incorrect", __LINE__);
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in.good()) 
    {
        printError("can`t open file for reading input data", __LINE__);
        return 1;
    }
    std::string s;
    std::map<std::string, int> dict;
    // При помощи std::map подсчитываем частоту вхождения каждого слова в текст
    std::for_each(std::istream_iterator<std::string>(in), 
                std::istream_iterator<std::string>(), [&](const std::string& word) { dict[word]++; });
    std::vector<pair> vecCountDict;
    // Копируем пары ключ-значение (слово-частота) в вектор для дальнейшей сорт-ки
    std::copy(dict.begin(), dict.end(), std::back_inserter(vecCountDict));
    // Ф-ия сравнения для метода std::sort
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
        printError("can`t open file to writing output data", __LINE__);
        return 1;
    }
    // Выводим частоты слов в порядке невозрастания в результирующий файл
    std::for_each(vecCountDict.begin(), vecCountDict.end(), 
                [&](const pair& p) { out << p.second << " " << p.first << "\n"; });
    return 0;
}