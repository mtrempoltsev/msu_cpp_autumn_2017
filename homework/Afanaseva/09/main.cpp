#include <iostream>
#include <string>

#include <stdexcept>

#include <vector>
#include <utility>
#include <fstream>

#include <iterator>
#include <algorithm>

using namespace std;

/*
Программе через аргументы командной строки передают два имени файлов.
Первое имя - текстовый файл в котором слова разделены пробелами,
его надо прочесть, составить частотный словарь "слово" - "сколько раз встречается".
После этого надо отсортировать словарь по частоте и вывести во второй файл (его имя - второй аргумент).
*/

class DictionaryError : public std::runtime_error
{
public:
    DictionaryError() : std::runtime_error("")
    {}

    DictionaryError(std::string message) : std::runtime_error("Dictionary error occured: " + message)
    {}

    virtual ~DictionaryError() throw()
    {}

    virtual const char* what() const throw()
    {
        return mMsg.c_str();
    }

protected:
    std::string mMsg;
};

//  ============================================================================================
//  ============================================================================================
//  ============================================================================================

class Dictionary
{
private:
    using data_type = std::pair<int, std::string>;
    std::vector<data_type> data_;
public:
    Dictionary(std::string input_filename)
    {
        std::ifstream file(input_filename);
        if (!file)
        {
            throw DictionaryError("can't open file to read " + input_filename);
            return;
        }
        while (file.good())
        {
            std::string s;
            file >> s;

            //cout << "Add: " << s << endl;
            data_.push_back(std::make_pair(1, s));
        }
        data_.pop_back();
    }

    void sort_and_flatter()
    {
        auto recount = [this](data_type& temp_x)
        {
            auto num = std::count_if(data_.begin(), data_.end(), [&temp_x](data_type& x){return x.second == temp_x.second;});
            temp_x.first = num;
        };
        std::for_each(data_.begin(), data_.end(), recount);
        std::sort(data_.begin(), data_.end(), [](data_type& x, data_type& y) { return x > y; });
        const auto last = std::unique(data_.begin(), data_.end());

        data_.erase(last, data_.end());
    }

    void write(std::string output_filename)
    {
        std::ofstream file(output_filename);
        if (!file)
        {
            throw DictionaryError("can't open file to write "  + output_filename);
            return;
        }

        auto print = [&file](data_type x)
        {
            file << x.first << " " << x.second << endl;
        };
        std::for_each(data_.begin(), data_.end(), print);

    }
};


int main(int argc, char *argv[])
{
    std::string input_name;
    std::string output_name;

    if (argc < 3)
    {
        std::cout << "Not enough arguments. Try: '" << argv[0] << " input.file output.file'"<< std::endl;
        return -1;
    }

    input_name = argv[1];
    output_name = argv[2];
    try
    {
        Dictionary dict = Dictionary(input_name);
        dict.sort_and_flatter();
        dict.write(output_name);
    }
    catch (const DictionaryError& e)
    {
        std::cout << e.what() << std::endl;
        return -2;
    }
    return 0;
}
