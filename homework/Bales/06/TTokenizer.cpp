#include "TTokenizer.h"

extern std::unordered_map<std::string, double> Constants;

TTokenizer::TTokenizer(const char*& expr) {
    _expr = expr;
}

TTokenizer::~TTokenizer() {
    _expr = nullptr;
}

std::pair<std::string, Token> TTokenizer::GetToken() {
    while (const auto ch = *(this->_expr++)) {
        switch (ch) {
            case ' ': continue;
            case '+': return std::make_pair("+", Token::Plus);
            case '-': return std::make_pair("-", Token::Minus);
            case '*': return std::make_pair("*", Token::Mul);
            case '/': return std::make_pair("/", Token::Div);
            case '(': return std::make_pair("(", Token::OpenBracket);
            case ')': return std::make_pair(")", Token::CloseBracket);
        }

        if (ch >= '0' && ch <= '9') {
            std::string str { ch };
            while (const auto n_ch = *(this->_expr++)) {
                if ((n_ch >= '0' && n_ch <= '9') || n_ch == '.')
                    str += n_ch;
                else break;
            }
            this->_expr--;
            return std::make_pair(str, Token::Number);
        }
        else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            std::string str { ch };
            while (const auto n_ch = *(this->_expr++)) {
                if ((n_ch >= 'a' && n_ch <= 'z') || (n_ch >= 'A' && n_ch <= 'Z'))
                    str += n_ch;
                else break;
            }
            this->_expr--;
            return std::make_pair(str, Token::DefConstant);            
        }
        else return std::make_pair(std::string({ ch }), Token::Invalid);
    }
    return std::make_pair("", Token::End);
}

void TTokenizer::RetrieveToken() {
    this->_expr--;
}

/*
TExitCode TTokenizer::IsValidExpr(const char* expr) {
    char prevCh = *expr++; // токен, считанный на предыдущей итерации
    size_t cntOperators = 0; // кол-во операторов, используемых послед-но
    size_t cntBrackets = 0;
    bool isUsedFlaotPoint = false;
    std::string buf;
    while (prevCh) {
        if ((prevCh >= 'a' && prevCh <= 'z') || (prevCh >= 'A' && prevCh <= 'Z'))
            buf += prevCh;            
        else if (prevCh != ' ')
            break;
        prevCh = *expr++;
    }
    if (buf.length() > 0) {
        prevCh = buf.back();
        expr--;
        if (Constants.count(buf) == 0)
            return TExitCode::INCORRECT_INPUT;
    }
    if ((prevCh >= '0' && prevCh <= '9') || prevCh == '-' || prevCh == '('
        || buf.length() > 0) {
        if (prevCh == '-')
            cntOperators++;
        if (prevCh == '(')
            cntBrackets++;
        while (const auto ch = *expr++) {   
            switch (ch) {
                case ' ': continue;
                case '-': 
                    if ((prevCh >= '0' && prevCh <= '9') || cntOperators <= 1
                        || ((prevCh >= 'a' && prevCh <= 'z') || (prevCh >= 'A' && prevCh <= 'Z'))) { 
                        prevCh = ch;
                        cntOperators++;
                        continue;
                    }
                    else return TExitCode::INCORRECT_INPUT;
                case '+':                     
                case '*':
                case '/':
                    if ((prevCh >= '0' && prevCh <= '9') || prevCh == ')' 
                        || ((prevCh >= 'a' && prevCh <= 'z') || (prevCh >= 'A' && prevCh <= 'Z'))) { 
                        prevCh = ch;
                        cntOperators++;
                        continue;
                    }
                    else return TExitCode::INCORRECT_INPUT;
                case '0':
                    if (prevCh == '/')
                        return TExitCode::ZERO_DIVISION;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if ((prevCh >= '0' && prevCh <= '9') 
                        || prevCh == '('
                        || prevCh == '.'
                        || cntOperators > 0) {
                        cntOperators = 0;
                        prevCh = ch;
                        continue;
                    }
                    else return TExitCode::INCORRECT_INPUT;
                case '.':
                    if (prevCh >= '0' && prevCh <= '9') {
                        if (!isUsedFlaotPoint) {
                            prevCh = '.';
                            isUsedFlaotPoint = !isUsedFlaotPoint;
                            continue;
                        }
                    }
                    return TExitCode::INCORRECT_INPUT;
                case '(':
                    if (prevCh == ')' || (prevCh >= '0' && prevCh <= '9') 
                        || ((prevCh >= 'a' && prevCh <= 'z') || (prevCh >= 'A' && prevCh <= 'Z')))
                        return TExitCode::INCORRECT_INPUT;
                    else {
                        prevCh = ch;
                        cntBrackets++;
                        continue;
                    }
                case ')':
                    if (cntBrackets > 0 
                        && ((prevCh >= '0' && prevCh <= '9') 
                            || prevCh == ')' 
                            || ((prevCh >= 'a' && prevCh <= 'z') || (prevCh >= 'A' && prevCh <= 'Z')))) { 
                        cntBrackets--;
                        prevCh = ch;
                        continue;
                    }
                    else return TExitCode::INCORRECT_INPUT;                
                default:     
                    if (((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) 
                        && (prevCh == '*' || prevCh == '/' || prevCh == '-' || prevCh == '+' || prevCh == '(')) {
                        prevCh = ch;
                        cntOperators = 0;
                        std::string str { ch };
                        while (const auto nCh = *expr++) {
                            if ((nCh >= 'a' && nCh <= 'z') || (nCh >= 'A' && nCh <= 'Z')) {
                                str += nCh;
                                prevCh = nCh;
                            }
                            else break;
                        }
                        expr--;
                        if (Constants.count(str) > 0) {
                            continue;                            
                        }
                        else return TExitCode::INCORRECT_INPUT;    
                    }
                    else return TExitCode::INCORRECT_INPUT;
            }
        }
        if (cntOperators > 0 || cntBrackets > 0) {
            return TExitCode::INCORRECT_INPUT;
        }
    }
    else return TExitCode::INCORRECT_INPUT;
    return TExitCode::OK;    
}
*/