#include <fstream>
#include <iostream>
#include <map>

class Counter {
public:
	Counter& read(char* const fname) {
		std::string word;
		std::ifstream file(fname);
		check_fstream_open(file);
		
		file >> word;
		while (file.good()) {
		    ++freqs.emplace(word, 0).first->second;
		    file >> word;
		}
		return *this;
	}

	Counter& write(char* const fname) {
		std::ofstream file(fname);
		check_fstream_open(file);
	
		for (auto it = freqs.rbegin(); it != freqs.rend(); ++it) { // std::map is ordered
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
	Counter c;
	c.read(argv[1]).write(argv[2]);
	return 0;
}