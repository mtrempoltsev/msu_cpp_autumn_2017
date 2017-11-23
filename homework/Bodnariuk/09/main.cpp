// Vasilii Bodnariuk

#include <iostream>
#include <string>
#include <fstream>

#include "counter.hpp"

int main(int argc, char* argv[])
{
    bool error_while_processing = false;
    if(argc != 2)
    {
        std::ifstream input_file(argv[1]);
        std::ofstream output_file(argv[2]);
        if(! input_file) {
            std::cout << "input file `" << argv[1] << "` doesn't exist" << '\n';
            error_while_processing = true;
        } else if(! output_file) {
            std::cout << "output file `" << argv[2] << "` is not accessable" << '\n';
            error_while_processing = true;
        } else {
            auto c = Counter();
            std::string word;
            while (input_file >> word)
            {
              c.add_word(word);
            }
            input_file.close();

            for (auto const& x : c.get_counts())
            {
              output_file << x.first <<  ' ' << x.second << '\n';
            }
            output_file << std::endl;
            output_file.close();
        }
    } else {
        std::cout << "invalid count of arguments" << '\n';
        std::cout << "usage: " << argv[0] << " input_file output_file" << '\n';
    }

    return error_while_processing ? -1 : 0;
}
