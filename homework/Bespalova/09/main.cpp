#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Error
{
    string message;
public:
    Error(string&& message_)
    {
        message = message_;
    }
    const string getMessage() const
    {
        return message;
    }
};

class Dictionary
{
private:
    string input;
    string output;
    vector<pair<string, int>> dict;
    unordered_map <string, int> m_dict;
    
    void read_words();
    void sort_dict();
    void write_sorted();
    
public:
    void execute();
    Dictionary(string input_, string output_);
};

Dictionary::Dictionary(string input_, string output_)
{
    input = input_;
    output = output_;
}

void Dictionary::read_words()
{
    ifstream f_input(input);
    if(!f_input)
        throw Error("invalid input filename");
    
    while(f_input)
    {
        string str;
        f_input >> str;

        if (m_dict.find(str) == m_dict.end())
            m_dict.insert({str, 1});
        else
            m_dict[str]++;
        
        if (f_input.eof())
            break;
    }
    f_input.close();
    
    dict = vector<pair<string, int>>(m_dict.begin(), m_dict.end());
}

void Dictionary::sort_dict()
{
    auto comp = [](const pair<string, int>& pair1, const pair<string, int>& pair2)
    {
        if (pair1.second == pair2.second)
            return pair1.first > pair2.first;
        else
            return pair1.second < pair2.second;
    };
    sort(dict.begin(), dict.end(), comp);
}

void Dictionary::write_sorted()
{
    ofstream f_output(output);
    if (!f_output)
        throw Error("output file can't be open");
    
    while(!dict.empty())
    {
        f_output << dict.back().second << " " << dict.back().first << endl;
        dict.pop_back();
    }
    
    f_output.close();
}

void Dictionary::execute()
{
    read_words();
    sort_dict();
    write_sorted();
}

int main(int argc, const char * argv[])
{
    try
    {
        if (argc != 3)
            throw Error("invalid arguments number");
        
        Dictionary dict(argv[1], argv[2]);
        dict.execute();
        
        return 0;
    }
    catch (Error E)
    {
        cerr << "Error: " << E.getMessage() << endl;
        return 1;
    }
    catch(...)
    {
        return 1;
    }
  
}
