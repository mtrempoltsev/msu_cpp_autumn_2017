#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

class Frequency_Calc
{
    std::map<std::string, int> freq_dict_;
    std::vector<std::pair<std::string, int> > freq_array_;
    const char* in_;
    const char* out_;

    void read_input()
    {
        std::string s;
        std::ifstream in(in_);
        if (!in)
            throw "Cant open input file\n";

        while (in >> s)
        {
            if (freq_dict_.find(s) != freq_dict_.end())
                freq_dict_[s] += 1;
            else
                freq_dict_[s] = 1;
        }

        in.close();
    }

    void sort()
    {
        std::copy(freq_dict_.begin(), freq_dict_.end(), std::back_inserter(freq_array_));
        std::sort(freq_array_.begin(), freq_array_.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b){return a.second > b.second;});
    }

    void print_output()
    {
        std::ofstream out(out_);
        if (!out)
            throw "Cant open output file\n";

        for (auto i: freq_array_)
            out << i.second << " " << i.first << std::endl;

        out.close();
    }

public:
    Frequency_Calc(const char* in, const char* out): in_(in), out_(out)
    {
    }

    void execute()
    {
        read_input();
        sort();
        print_output();
    }
};

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "need 2 filenames\n";
        return 1;
    }

    Frequency_Calc freq(argv[1], argv[2]);
    try
    {
        freq.execute();
    } catch (const char* ms){
        std::cout << ms << std::endl;
        return 1;
    }

    return 0;
}
