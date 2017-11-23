#include <fstream>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <map>
#include <string>

//unordered_map with {(word from text: word's frequency)...}
using NumByWord = std::unordered_map<std::string, int>;
//iterator of NumByWord container
using NumIter = NumByWord::const_iterator;
//map of {(frequency of the word:
//           iterator of place in NumByWord where that pair is)...}
using WordIterByNum = std::multimap<int, NumIter>;

/* that procedure splits a string by space character
and for each word in string increments its frequency
in textfile using NumByWord structure 'counter' */
void str_word_counter(std::string s, NumByWord& counter)
{
  std::size_t pos = 0;
  const std::string ws = " ";
  while (pos != s.size()) {
    std::size_t from = s.find_first_not_of(ws, pos);
    if (from == std::string::npos) {
        break;
    }
    std::size_t to = s.find_first_of(ws, from+1);
    if (to == std::string::npos) {
        to = s.size();
    }

    std::string word;
    word = s.substr(from, to);

    auto iter = counter.find(word);

    if (iter == counter.end()) {
      std::pair<std::string,double> tmp_pair(word,1);
      counter.insert(tmp_pair);
    } else {
      counter[word]++;
    }


    pos = to;
  }
}

/* this function applies str_word_counter() procedure
for each string in input textfile 'file' and returns NumByWord structure
with words' frequencies */
NumByWord word_counter(std::ifstream &file)
{
  std::unordered_map<std::string, int> counter;
  while (file.good())
  {
    std::string s;
    file >> s;
    str_word_counter(s, counter);
  }
  return counter;
}

/* this function creates WordIterByNum structure to define an ascending
order of words' frequencies*/
WordIterByNum sort_by_value(const NumByWord &counter)
{
    WordIterByNum proxy;
    for (auto it = counter.begin(), end = counter.end();
        it != end; ++it)
    {
       std::pair<int, NumIter> tmp = std::make_pair(it->second, it);
       proxy.emplace(it->second, it);
    }
    return proxy;
}

/* this procedure writes to output textfile 'file' contents of
NumByWord structure in reverse order which determined in
WordIterByNum structure 'proxy';

this procedure works as long as NumByWord structure is available in main()*/
void output(WordIterByNum &proxy, std::ofstream &file)
{
  for (auto it = proxy.rbegin(); it != proxy.rend(); ++it )
    file << " " << it->second->first << ":" << it->second->second << std::endl;
}


int main(int argc, char *argv[])
{
  //read file
  std::ifstream ifile(argv[1]);
  std::unordered_map<std::string, int> counter;

  //count words' frequencies
  counter = word_counter(ifile);

  //create proxy structure to define order of frequencies
  auto proxy = sort_by_value(counter);

  //output resuls
  std::ofstream ofile(argv[2]);
  output(proxy, ofile);

  return 0;
}
