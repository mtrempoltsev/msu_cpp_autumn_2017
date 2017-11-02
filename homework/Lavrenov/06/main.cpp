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
    
    //string expression = "(8 - 7 / 2) * 3";
    Expression<double, DoubleParser>* expr = new Expression<double, DoubleParser>(expression);
    cout << expr->execute() << endl;
    delete expr;
    return 0;
}

