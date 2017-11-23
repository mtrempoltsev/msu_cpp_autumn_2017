// Vasilii Bodnariuk

#include <unordered_map>
#include <vector>
#include <string>

class Counter {
private:
    std::unordered_map<std::string, int> words_map;
public:
    std::vector<std::pair<int, std::string>> get_counts();
    bool add_word(std::string);
};
