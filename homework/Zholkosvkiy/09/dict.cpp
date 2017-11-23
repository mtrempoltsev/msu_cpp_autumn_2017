#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>


int main(int argc, char** argv)
{
	try
	{
		//check args
		if(argc != 3)
		{
			throw std::runtime_error("wrong input");
		}
		std::cout << "Input file: " << argv[1] << std::endl;
		std::cout << "Output file: " << argv[2] << std::endl;

		std::vector < std::pair<std::string, int> > wordsList;
		std::string word;

		//read file
		std::ifstream file_i(argv[1]);
		if (!file_i)
		{
			throw std::runtime_error("can't open file to read");
		}

		while (file_i.good())
		{
			file_i >> word;
			if(file_i.eof())
			{
				break;
			}

			//check if the word in wordsList
			auto wordInDict = std::find_if(wordsList.begin(), wordsList.end(), [&word](auto x){ return (x.first == word); });

			//if it is - increase quantity
			if(wordInDict != wordsList.end())
			{
				wordInDict->second++;
			}
			//add word to wordsList
			else
			{
				auto newPair = std::pair<std::string, int>(word, 1);
				wordsList.push_back(newPair);
			}
		}
		file_i.close();

		//sort
		std::sort(wordsList.begin(), wordsList.end(), [](auto x, auto y) { return (x.second > y.second); });

		//open file to write
		std::ofstream file_o(argv[2]);
		if (!file_o)
		{
		    throw std::runtime_error("can't open file to write");
		}
		for (int i = 0; i < wordsList.size(); i++)
		{
			file_o << wordsList[i].second << " " << wordsList[i].first << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
	catch(...)
	{
		std::cout << "Unknown error:" << std::endl;
		return 1;
	}
	return 0;
}
