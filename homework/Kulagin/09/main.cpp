#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class DictError : public runtime_error {

public:
    DictError(string err_msg) : runtime_error("Dict error: " + err_msg) {}
};


class Dict {

public:
    using TIntString = pair<int, string>;

    Dict(string _infile) {
        ifstream file(_infile);

        if (!file) {
            throw DictError("cannot open file \"" + _infile + "\"");
        }

        while (file.good()) {
            string str;
            file >> str;

            data_.push_back(std::make_pair(1, str));
        }

        data_.pop_back();

        sort();
    }

    void write_to_file(string _outfile) {
        ofstream file(_outfile);

        if (!file) {
            throw DictError("cannot open file \""  + _outfile + "\"");
        }

        auto write_elem = [&file](TIntString x) {
            file << x.first << " " << x.second << endl;
        };

        std::for_each(data_.begin(), data_.end(), write_elem);
    }

    void sort() {
        auto get_counts = [this](TIntString & is_tmp) {
            auto cnt = count_if(data_.begin(), data_.end(),
            [&is_tmp](TIntString & is) {
                return is.second == is_tmp.second;
            }
                               );

            is_tmp.first = (int)cnt;
        };

        auto sort = [](TIntString & x, TIntString & y) {
            return x > y;
        };

        std::for_each(data_.begin(), data_.end(), get_counts);
        std::sort(data_.begin(), data_.end(), sort);

        const auto uniq = unique(data_.begin(), data_.end());

        data_.erase(uniq, data_.end());
    }

private:
    vector<TIntString> data_;
};


int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Usage: ./a.out <infile> <outfile>" << endl;

        exit(1);
    }

    string infile = argv[1];
    string outfile = argv[2];

    try {
        Dict dict = Dict(infile);
        dict.write_to_file(outfile);
    } catch (const DictError& e) {
        cout << e.what() << endl;

        exit(1);
    }

    return 0;
}
