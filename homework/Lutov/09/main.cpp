#include <algorithm>
#include <cinttypes>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>

int
main(int argc, char **argv)
{
  try {
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " input_file output_file" << std::endl;
      return 1;
    } else {
      std::ifstream ifs(argv[1]);
      if (!ifs.is_open()) {
        std::cerr << "Cannot open file '" << argv[1] << "' for reading" << std::endl;
        return 1;
      }

      std::ofstream ofs(argv[2]);
      if (!ofs.is_open()) {
        std::cerr << "Cannot open file '" << argv[2] << "' for writing" << std::endl;
        return 1;
      }

      std::string ws;
      std::unordered_multiset<std::string> counts;

      while (true) {
        ifs >> ws;
        if (!ifs.good()) {
          break;
        }

        counts.insert(ws);
      }

      std::set<std::string> words(counts.cbegin(), counts.cend());
      std::vector<std::pair<intmax_t, std::string>> result;
      result.reserve(words.size());

      for (const auto &w : words) {
        result.emplace_back(counts.count(w), w);
      }

      std::stable_sort(result.rbegin(), result.rend());

      for (const auto &p : result) {
        ofs << p.first << " " << p.second << std::endl;
      }

      ifs.close();
      ofs.close();

      return 0;
    }
  } catch (...) {
    return 1;
  }
}
