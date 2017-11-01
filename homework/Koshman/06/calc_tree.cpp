#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>
#include <unordered_map>

using namespace std;

static bool out_of_range_ = false;

std::unordered_map<std::string, double> constants =
        {
                {"Pi", 3.14},
                {"e",  2.7}
        };

enum class Token {
    Invalid,
    Minus,
    BinaryMinus,
    UnaryMinus,
    Plus,
    Mul,
    Div,
    Number,
    LeftBracket,
    RightBracket,
    End
};

/*
 * class for holding tokens and their values(in case of numbers/constants)
 * also has some useful methods
 */
template<typename T>
struct Token_value {
    explicit Token_value(Token token, T value = 0.0) : token(token), value(value) {}

    /*
     * true if token is an operator
     */
    bool isOperator() {
        if ((token == Token::Plus) ||
            (token == Token::BinaryMinus) ||
            (token == Token::UnaryMinus) ||
            (token == Token::Mul) ||
            (token == Token::Div))
            return true;
        else
            return false;
    }

    /*
     * true if token is a binary + -
     */
    bool isPM() {
        if ((token == Token::Plus) ||
            (token == Token::BinaryMinus))
            return true;
        else
            return false;
    }

    Token token;
    T value;
};

/*
 * node for the calculation tree
 */
template<typename T>
struct Node {
    /*
     * a leaf
     */
    Node(Token token, T value) :
            token(token), value(value) {}

    /*
     * a branch
     */
    Node(Token token, Node *left, Node *right) :
            token(token), left(left), right(right) {}

    Token token;
    T value = 0;
    Node *left = nullptr;
    Node *right = nullptr;
};

template<typename T>
bool isNumericToken(char c, const char *&text);

template<>
bool isNumericToken<int>(char c, const char *&text) {
    if (c == '0')
        return true;
    if (c >= '1' && c <= '9') {
        for (auto c = *text; ((c >= '0') && (c <= '9'));) {
            text++;
            c = *text;
        }
        return true;
    }
    return false;
}

template<>
bool isNumericToken<long>(char c, const char *&text) {
    return isNumericToken<int>(c, text);
}

template<>
bool isNumericToken<double>(char c, const char *&text) {
    bool past_dot = false;
    if (c == '0') {
        if (*text != '.')
            return true;
        past_dot = true;
        text++;
        if (*text == '\0')
            return false;
        c = *text++;
    }
    if (c >= '0' && c <= '9') {
        for (auto c = *text; ((c >= '0') && (c <= '9')) || c == '.';) {
            if (c == '.') {
                if (past_dot)
                    break;
                past_dot = true;
            }
            text++;
            c = *text;
        }
        return true;
    }
    return false;
}

template<typename T>
Token getToken(const char *&text) {

    while (const auto c = *text++) {

        switch (c) {
            case ' ':
                continue;
            case '-':
                return Token::Minus;
            case '+':
                return Token::Plus;
            case '*':
                return Token::Mul;
            case '/':
                return Token::Div;
            case '(':
                return Token::LeftBracket;
            case ')':
                return Token::RightBracket;
        }

        if (c == 'e')
            return Token::Number;
        if (c == 'P') {
            char d = *text;
            if (d == 'i') {
                text++;
                return Token::Number;
            } else
                return Token::Invalid;
        }

        if (isNumericToken<T>(c, text))
            return Token::Number;

        return Token::Invalid;
    }
    return Token::End;

};

template<typename T>
T getNumber(const char *start, const char *end) {

    T result = 0;
    T max = numeric_limits<T>::max();

    while (*start == ' ')
        ++start;
    if (*start == 'e')
        return (T) constants["e"];
    if (*start == 'P')
        return (T) constants["Pi"];

    while (start < end) {
        if (((max - (*start - 48)) / 10) < result)
            out_of_range_ = true;
        result = result * 10 + *start - 48;
        ++start;
    }

    return result;
}

template<>
double getNumber<double>(const char *start, const char *end) {

    double result = 0;
    double max = numeric_limits<double>::max();

    while (*start == ' ')
        ++start;
    if (*start == 'e')
        return constants["e"];
    if (*start == 'P')
        return constants["Pi"];

    double multiplier = 10;
    double divisor = 1;
    while (start < end) {
        if (*start == '.') {
            multiplier = 1;
            divisor = 10;
            ++start;
            continue;
        }
        if (((max - (*start - 48) / divisor) / multiplier) < result)
            out_of_range_ = true;
        result = result * multiplier + (*start - 48) / divisor;
        if (divisor != 1)
            divisor *= 10;
        ++start;
    }

    return result;
}

/*
 * create a calculation tree from Token_values vector
 * by finding the operator with least priority and splitting
 */
template<typename T>
Node<T> *createTree(vector<Token_value<T>> vector) {

    Node<T> *nodeP;

    //variables for keeping count of brackets
    int min_priority = -1;
    int current_priority = 0;

    //variables describing current operator candidate to split on
    bool is_PM = false;
    bool is_unary_minus = false;

    //does current operator have less priority?
    bool changed = false;

    int opIndex = -1;
    int numberIndex = -1;
    int count = 0;
    for (auto token_v : vector) {

        if (token_v.token == Token::Number) {
            numberIndex = count;
            count++;
            continue;
        }

        if (token_v.isOperator()) {
            if ((min_priority == -1) || (current_priority < min_priority)) {
                changed = true;
            } else if (current_priority == min_priority) {
                if (token_v.isPM())
                    changed = true;
                else if (not is_PM) {
                    if (token_v.token == Token::UnaryMinus) {
                        if (opIndex == -1)
                            changed = true;
                    } else
                        changed = true;
                }
            }

            if (changed) {
                opIndex = count;
                min_priority = current_priority;
                is_unary_minus = (token_v.token == Token::UnaryMinus);
                is_PM = token_v.isPM();
                changed = false;
            }

        }
        if (token_v.token == Token::LeftBracket) {
            current_priority++;
        }
        if (token_v.token == Token::RightBracket) {
            current_priority--;
        }
        count++;
    }

    if (opIndex == -1) {
        nodeP = new Node<T>(Token::Number, vector[numberIndex].value);
        return nodeP;
    }
    std::vector<Token_value<T>> left_v;
    std::vector<Token_value<T>> right_v;

    //min_priority = number of brackets we need to trim in the
    //beginning and end of the vector
    for (int count_2 = 0; count_2 < count; ++count_2) {
        if (count_2 + min_priority >= count)
            break;
        if (count_2 < min_priority) {
            continue;
        }
        if (count_2 < opIndex) {
            left_v.push_back(vector[count_2]);
        }
        if (count_2 > opIndex) {
            right_v.push_back(vector[count_2]);
        }
    }

    Node<T> *leftNode;
    if (is_unary_minus) {
        leftNode = new Node<T>(Token::Number, 0);
    } else
        leftNode = createTree<T>(left_v);

    nodeP = new Node<T>(vector[opIndex].token, leftNode, createTree<T>(right_v));

    return nodeP;

}

/*
 * function for solving the calculation tree
 */
template<typename T>
T solveTree(Node<T> *node) {
    if (node->token == Token::Number) {
        T result = node->value;
        delete node;
        return result;
    }
    T lValue = solveTree(node->left);
    T rValue = solveTree(node->right);
    T min = numeric_limits<T>::lowest();
    T max = numeric_limits<T>::max();
    auto token = node->token;
    delete node;
    switch (token) {
        case Token::BinaryMinus: {
            if ((rValue > 0) && (min + rValue > lValue))
                out_of_range_ = true;
            else if ((rValue < 0) && (max + rValue < lValue))
                out_of_range_ = true;
            return lValue - rValue;
        }
        case Token::UnaryMinus: {
            if ((rValue < 0) && (rValue + max < 0))
                out_of_range_ = true;
            return -rValue;
        }
        case Token::Plus:
            if ((rValue < 0) && (min - rValue > lValue))
                out_of_range_ = true;
            else if ((rValue > 0) && (max - rValue < lValue))
                out_of_range_ = true;
            return lValue + rValue;
        case Token::Mul:
            if ((lValue > 0) && (rValue > 1) && (max / rValue < lValue))
                out_of_range_ = true;
            else if ((lValue > 0) && (rValue < (min / max)) && (min / rValue < lValue))
                out_of_range_ = true;
            else if ((lValue < 0) && (rValue < (max / min)) && (max / rValue > lValue))
                out_of_range_ = true;
            else if ((lValue < 0) && (rValue > 1) && (min / rValue > lValue))
                out_of_range_ = true;
            return lValue * rValue;
        case Token::Div: {
            if (rValue == 0)
                throw std::overflow_error("Exception: zero division");
            if ((lValue > 0) && (0 < rValue) && (rValue < 1) && (max * rValue < lValue))
                out_of_range_ = true;
            else if ((lValue > 0) && (0 > rValue) && (rValue > (max / min)) && (min * rValue < lValue))
                out_of_range_ = true;
            else if ((lValue < 0) && (0 > rValue) && (rValue > (min / max)) && (max * rValue > lValue))
                out_of_range_ = true;
            else if ((lValue < 0) && (0 < rValue) && (rValue < 1) && (min * rValue > lValue))
                out_of_range_ = true;
            return lValue / rValue;
        }
        default:
            throw std::invalid_argument("Exception: could not solve tree");
    }
}

/*
 * main class that receives the expression,
 * checks its validity and has
 * a method for calculating it
 */
template<typename T>
struct Calculator {

    explicit Calculator(char const *text) :
            ZeroDivision(false),
            n_tokens(0),
            result(0),
            text(text) {}

    bool isValid() {
        const char *end = text;
        bool invalid = false;
        bool is_operator = true;
        bool l_bracket = false;
        int openBrackets = 0;

        auto token = getToken<T>(end);
        while (token != Token::End) {
            n_tokens++;
            switch (token) {
                case Token::Invalid: {
                    invalid = true;
                    break;
                }
                case Token::Number: {
                    if ((not is_operator) && (not l_bracket))
                        invalid = true;
                    l_bracket = false;
                    is_operator = false;
                    break;
                }
                case Token::Minus: {
                    is_operator = true;
                    l_bracket = false;
                    break;
                }
                case Token::LeftBracket: {
                    if ((not is_operator) && (not l_bracket))
                        invalid = true;
                    l_bracket = true;
                    is_operator = false;
                    openBrackets++;
                    break;
                }
                case Token::RightBracket: {
                    if (is_operator || l_bracket || (openBrackets < 1))
                        invalid = true;
                    l_bracket = false;
                    is_operator = false;
                    openBrackets--;
                    break;
                }
                default: {
                    if (is_operator || l_bracket)
                        invalid = true;
                    is_operator = true;
                }
            }
            if (invalid)
                break;
            token = getToken<T>(end);
        }
        if (invalid || is_operator || openBrackets)
            return false;
        return true;
    }

    void tokenize() {
        const char *ptr1 = text;
        const char *ptr2 = text;
        bool prev_is_number_or_rbracket = false;

        for (int i = 0; i < n_tokens; ++i) {
            auto token = getToken<T>(ptr2);

            if (token == Token::Number) {
                vector.emplace_back(token, getNumber<T>(ptr1, ptr2));
                prev_is_number_or_rbracket = true;
            } else if (token == Token::Minus) {
                if (prev_is_number_or_rbracket)
                    vector.emplace_back(Token::BinaryMinus);
                else
                    vector.emplace_back(Token::UnaryMinus);
                prev_is_number_or_rbracket = false;
            } else {
                if (token == Token::RightBracket)
                    prev_is_number_or_rbracket = true;
                else
                    prev_is_number_or_rbracket = false;
                vector.emplace_back(token);
            }
            ptr1 = ptr2;
        }
    }

    T calculate() {
        this->tokenize();
        Node<T> *tree;
        tree = createTree<T>(vector);
        try {
            result = solveTree(tree);
        } catch (std::overflow_error &e) {
            ZeroDivision = true;
            return 0;
        }
        return result;
    }

    bool ZeroDivision;
    int n_tokens;
    T result;
    char const *text;
    std::vector<Token_value<T>> vector;
};

template<typename T>
int use_calculator(char const *text) {

    bool isvalid;
    T result;
    Calculator<T> calculator(text);
    isvalid = calculator.isValid();

    if (not isvalid) {
        cout << "Invalid expression";
        return 1;
    } else {
        result = calculator.calculate();
        if (calculator.ZeroDivision) {
            cout << "Exception: zero division";
            return 1;
        }
        if (out_of_range_)
            cout << "Overflow detected" << endl;
        cout << result;
    }

    return 0;
}


int main(int argc, char const *argv[]) {
    if (argc == 1) {
        cout << "No expression provided";
        return 1;
    }
    char const *text = argv[1];
    if (argc == 2) {
        return use_calculator<double>(text);
    } else {
        switch (argv[2][0]) {
            case 'd': {
                return use_calculator<double>(text);
                break;
            }
            case 'i': {
                return use_calculator<int>(text);
                break;
            }
            case 'l': {
                return use_calculator<long>(text);
                break;
            }
            default: {
                cout << "invalid type, choices are: \n d \t double \n i \t int \n l \t long";
                return 1;
            }
        }
    }
    return 1;
}
