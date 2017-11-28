#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <utility>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
if (argc < 3)
{
    std::cout << "Not enough arguments. Try: '" << argv[0] << " input.file output.file'"<< std::endl;
    return -1;
}
//в uniq хранится уникальные слова,в a хранится их количество
map<string,int> a;
set<string> uniq;
std::ifstream in(argv[1]);
std::ofstream out(argv[2]);

while (in.good())
{
    string s;
    in >> s;
    uniq.insert(s);
    a[s]++;
}
uniq.erase("\n");
uniq.erase("");
uniq.erase(" ");
//в set все упорядочено по возрастанию,а нам нужно по убыванию поэтому я на -1 здесь умножил,чтобы как нужно упорядочилась
set<pair<int,string> > dict;
for(auto j : uniq){
    dict.insert(make_pair((-1)*a[j],j));
}
for(auto j:dict){
    out<<(-1)*j.first<<" "<<j.second<<endl;
}
return 0;
}
