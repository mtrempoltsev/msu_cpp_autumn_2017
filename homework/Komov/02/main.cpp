#include <iostream>

using namespace std;

int term(const char*& input);
int factor(const char*& input);

enum Token {

    Plus,
    Minus,
    Multiply,
    Divide,
    Number,
    Invalid,
    End
};

// Calculator grammatics:

// expr = term
//     | expr - term
//     | expr + term
// term = prim
//     | term / factor
//     | term * factor
// factor = number
//     | -number
// number = [0-9]+

Token next(const char*& input) {

    while (char c = *input++) {

        switch (c) {

            case ' ' : continue;
            case '+' : return Token::Plus;
            case '-' : return Token::Minus;
            case '*' : return Token::Multiply;
            case '/' : return Token::Divide;
        }

        if ((c <= '9') && (c >= '0'))
            return Token::Number;
        else
            return Token::Invalid;
    }

    return Token::End;
}

// Summands

int expr(const char*& input) {

    int result = term(input);
    Token str = next(input);

    if (str != Token::End)
        if (str == Token::Minus)
            return result - expr(input);
        else
            return result + expr(input);
    else
        return result;
}

// Factors

int term(const char*& input) {

    int result = factor(input);
    Token str = next(input);

    if ((str == Token::Multiply) || (str == Token::Divide))
        if (str == Token::Divide)
            return result / term(input);
        else
            return result * term(input);
    else {

        --input;
        return result;
    }
}

// Atoms

int factor(const char*& input) {

    char str = next(input);
    int result = 0;

    if (str == Token::Number) {

        input--;
        char str = *input;

        while ((str <= '9') && (str >= '0')) {

            result = str + 10 * result - '0';
            str = *++input;
        }

        return result;
    }

    else
        // unary minus operator
        return -factor(input);
}

int main(int argc, const char* argv[]) {

    if (argc != 2) {

        cout << "BAD INPUT" << endl;
        return 0;
    }

    const char* input = argv[1];

    cout << expr(input) << endl;

    return 1;
}
