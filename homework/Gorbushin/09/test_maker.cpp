#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <fstream>

int main(int argc, char **argv) {
    std::ofstream output(argv[2]), input(argv[1]);
    srand(time(NULL));
    constexpr size_t size = 'z' - 'a' + 1;
    char letters[size];
    for (int i = 0; i < size; i++) {
        letters[i] = 'a' + i;
    }

    std::vector<std::pair<int, int> > freq(size);
    std::vector<int> order(size, 0);
    for (int i = 0; i < size; i++) {
        order[i] = i;
        freq[i] = std::make_pair(rand() % 300, i);
    }
    
    std::random_shuffle(order.begin(), order.end());

    std::sort(freq.begin(), freq.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
        return a.first > b.first;
    });

    /* чтобы не было строк вида
       29 z
       29 r

       тогда тестировано затрудняется, чтобы учитывать такие случаи
    */
    auto end = std::unique(freq.begin(), freq.end(), [](std::pair<int, int> &a, std::pair<int, int> &b) {
        return a.first == b.first;
    });
    auto begin = freq.begin();
    while (begin != end) {
        for (int j = 0; j < (*begin).first; j++) {
            input << letters[(*begin).second] << ' ';
        }
        if ((*begin).first) {
            output << (*begin).first << ' ' << letters[(*begin).second] << std::endl;
        }
        begin++;
    }
    
    return 0;
}
