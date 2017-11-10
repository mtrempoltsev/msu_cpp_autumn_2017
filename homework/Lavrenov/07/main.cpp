#include "expression.h"
#include "intparser.h"
#include "doubleparser.h"
#include "longparser.h"

using namespace std;

//3 * - Pi + ((4 * 6) - 9)
//4 * ((4 * 6) - 9)

int main(int argc, char** argv)
{
    
    if(argc < 2){
        cerr<<"no expression\n";
        exit(1);
    }
    string expression = argv[1];
    
    //string expression = "3 * - Pi + ((4 * 6) - 9)";
    try{
        Expression<double, DoubleParser> expr(expression);
        cout << expr.execute() << endl;
    }catch(std::out_of_range& e){
        cerr<<"error parsing token(too big value)\n";
    }catch(std::invalid_argument& e){
        cerr<<"syntax error\n";
    }catch(std::bad_cast& e){
        cerr<<"error working with table of variables\n";
    }catch(...){
        cerr<<"unknown error\n";
    }

    return 0;
}

