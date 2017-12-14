#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
    //validate args parameters
    if (argc != 3) {
        throw runtime_error("Invalid number of args");
        return 1;
    }
    vector<pair<string, int> > dict;
    string buf;

    ifstream input(argv[1]);
    if (!input) {
        throw runtime_error("File can not open");
        return 1;
    }

    input >> buf;
    while (!input.eof()) {
		
        auto word = find_if(dict.begin(), dict.end(), [&buf](auto x) { return (x.first == buf); });
        
        //increment
        if (word != dict.end()) {
            word->second++;
        }
        //add pair to dict
        else {
            auto PairBuf = pair<string, int>(buf, 1);
            dict.push_back(pair<string, int>(buf, 1));
        }
        input >> buf;
    }
    input.close();
    
    //sort dict
    sort(dict.begin(), dict.end(), [](auto x, auto y) { return (x.second > y.second); });

    //write
    ofstream output(argv[2]);
    if (!output) {
        throw runtime_error("File can not write");
        return 1;
    }
    for (int i = 0; i < dict.size(); i++) {
        output << dict[i].second << " " << dict[i].first << endl;
    }
    return 0;
}
