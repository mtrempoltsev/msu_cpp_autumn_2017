#include <fstream>
#include <iostream>
#include <map>
#include <vector>

class Counter {
public:
    Counter& read(char* const fname) {
        std::string word;
        std::ifstream file(fname);
        check_fstream_open(file);
        
        while (file >> word) {
            ++freqs.emplace(word, 0).first->second;
        }
        return *this;
    }

    Counter& write(char* const fname) {
        using pair = std::pair<std::string, int>;
        std::ofstream file(fname);
        check_fstream_open(file);

        std::vector<pair> freqs_sorted(freqs.begin(), freqs.end());
        std::sort(freqs_sorted.begin(), freqs_sorted.end(), [](pair a, pair b){ return a.second > b.second; });
    
        for (auto it = freqs_sorted.begin(); it != freqs_sorted.end(); ++it) {
            file << it->first << " " << it->second << std::endl;
        }
        return *this;
    }

private:
    void check_fstream_open(const std::ios& fstream) {
        if (!fstream) {
            std::cout << "Can't open file.";
            exit(1);
        }
    }

    std::map<std::string, int> freqs;
};


int main(int argc, char* const argv[]) {
    if (argc != 3) {
        std::cout << "Invalid arguments count" << std::endl;
        exit(1);
    }
    Counter().read(argv[1]).write(argv[2]);
    return 0;
}