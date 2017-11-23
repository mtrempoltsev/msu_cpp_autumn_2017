#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using word = std::pair<std::string, int>;    // word itself and its frequency

class Dictionary
{
public:
    Dictionary(const char* input_file, const char* output_file): input(input_file), output(output_file) {}
    void makeDictionary()
    {
        readFromInputFile();
        sortWords();
        writeToOutputFile();
    }
private:
    const char* input;
    const char* output;
    std::vector<word> words;

    void readFromInputFile()
    {
        std::ifstream file_in(input);
        if (!file_in.good())
        {
            throw "Input file can not be open!";
        }
        while (file_in.good())
        {
            std::string s;
            file_in >> s;

            if(words.empty())
            {
                words.push_back(std::make_pair(s, 1));
            }
            else
            {
                bool is_word_in_dict = false;
                for (size_t i = 0; i < words.size(); i++)
                {
                    if(std::equal(s.begin(), s.end(), words[i].first.begin()))
                    {
                        words[i].second++;
                        is_word_in_dict = true;
                        break;
                    }
                }
                if (!is_word_in_dict)
                {
                    words.push_back(std::make_pair(s, 1));
                }
            }
        }
    }
    void sortWords()
    {
        std::sort(words.begin(), words.end(), [](word x, word y) { return x.second < y.second; });
    }
    void writeToOutputFile()
    {
        std::ofstream file_out(output);
        if (!file_out)
        {
            throw "Output file can not be open!";
        }

        while(!words.empty())
        {
            file_out << words.back().second << " " << words.back().first << std::endl;
            words.pop_back();
        }
    }
};
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "One of the files is not specified!" << std::endl;
        return 1;
    }
    Dictionary dict(argv[1], argv[2]);

    try
    {
        dict.makeDictionary();
    }
    catch (const char* error)
    {
        std::cout << error << std::endl;
        return 1;
    }
    return 0;
}
