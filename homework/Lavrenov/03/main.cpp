#include "expression.h"

using namespace std;

//3 * - Pi + ((4 * 6) - 9)
//4 * ((4 * 6) - 9)

int main(int argc, char** argv)
{
    
    //if(argc < 2){
        //cerr<<"no expression\n";
        //exit(1);
    //}
    //string expression = argv[1];
    
    string expression = "3 * - Pi + - ((4 * 6) - 9)";
    Expression* expr = new Expression(expression);
    cout << expr->execute() << endl;
    delete expr;
    return 0;
}

