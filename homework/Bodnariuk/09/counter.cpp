// Vasilii Bodnariuk

#include "counter.hpp"

#include <algorithm>
#include <functional>

std::vector<std::pair<int, std::string>> Counter::get_counts()
{
    std::vector<std::pair<int, std::string>> counted_items(words_map.size());

    std::transform(
        words_map.begin(),
        words_map.end(),
        counted_items.begin(),
        [](std::pair<std::string, int> elem){return std::pair<int, std::string> (elem.second, elem.first);}
    );

    std::sort(counted_items.begin(), counted_items.end(), std::greater<std::pair<int, std::string>>());

    return counted_items;
}

bool Counter::add_word(std::string word)
{
    auto exists = words_map.count(word) > 0;
    if(exists)
    {
        words_map[word] += 1;
    } else {
        words_map[word] = 1;
    }

    return exists;
}
