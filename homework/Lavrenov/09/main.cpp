#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 3){
        cerr<<"not enough arguments\n";
        exit(1);
    }

    std::string inputName = argv[1];// = "input.txt";
    std::string outputName = argv[2];// = "output.txt";

    std::ifstream input(inputName);
    std::ofstream output(outputName);

    if(!input){
        cerr << "wrong input\n";
        exit(2);
    }

    std::vector<pair<string, size_t>> dictionary;

    while (input.good()){
        std::string tmp;
        input >> tmp;
		if(tmp.empty())
			continue;
        auto where = find_if(dictionary.begin(), dictionary.end(),[tmp](pair<string, size_t> p){return p.first == tmp;});
        if(where == dictionary.end()){
            dictionary.push_back(pair<string, size_t>(tmp, 1));
        }else{
            ++((*where).second);
        }
    }

    sort(dictionary.begin(), dictionary.end(), [](pair<string, size_t> left, pair<string, size_t> right){
        return left.second > right.second;
    });
    for(auto word : dictionary){
        output << word.second << " " << word.first <<"\n";
    }
    cout<<"ok\n";
    return 0;
}

