#include <cctype>
#include <string>
#include <unordered_map>

/**
 * Describes type of token
 */
enum class TokenType
{
    OpenBracket,
    CloseBracket,
        
    Minus,
    Plus,
    Div,
    Mul,

    Number,
    Constant,

    Invalid,
    End
};

/**
 * Presents string as sequence of token
 */
class Tokenizer
{
    const char *_token_start;
    const char *_token_end;
    TokenType _token_type;

    /**
     * sets _token_end to end of numeric token
     */
    void scan_number() {
        const char *p = _token_start;
        while (std::isdigit(*p)) {
            p++;
        }
        _token_end = p;
    }

    /**
     * sets _token_end to end of constant token
     */
    void scan_constant() {
        const char *p  = _token_start;
        while (std::isalpha(*p)) {
            p++;
        }
        _token_end = p;
    }

    /**
     * returns token type based on it's first character
     */    
    TokenType get_token_type(char c) {
        switch (c) {
        case '(': return TokenType::OpenBracket;
        case ')': return TokenType::CloseBracket;
            
        case '-': return TokenType::Minus;
        case '+': return TokenType::Plus;
        case '*': return TokenType::Mul;
        case '/': return TokenType::Div;

        case '\0': return TokenType::End;
        }

        if (std::isdigit(c)) {
            return TokenType::Number;
        }

        if (std::isalpha(c)) {
            return TokenType::Constant;
        }

        return TokenType::Invalid;
    }

public:
    Tokenizer(const char *str): _token_start(str), _token_end(str) {
        next_token();
    }

    const char *token_start() {
        return _token_start;
    }

    const char *token_end() {
        return _token_end;
    }
   
    TokenType token_type() {
        return _token_type;
    }

    /**
     * changes focus to next token
     */
    void next_token() {
        _token_start = _token_end;
        while (std::isspace(*_token_start)) {
            _token_start++;
        }

        _token_type = get_token_type(*_token_start);
        if (_token_type == TokenType::End || _token_type == TokenType::Invalid) {
            _token_end = _token_start;
            return;
        }

        if (_token_type == TokenType::Number) {
            scan_number();
            return;
        }

        if (_token_type == TokenType::Constant) {
            scan_constant();
            return;
        }

        _token_end = _token_start + 1;
    }
};

/**
 * Describes errors which can occure during parsing
 */
struct ParsingError
{
    const char *point;
    const char *msg;
};

/**
 * parses & evaluates string during initialization
 * throws ParsingError if failed 
 * Grammar is
 * <expr> ::= <term> | <expr> + <term> | <expr> - <term>
 * <term> ::= <prim> | <term> * <prim> | <term> / <prim>
 * <prim> ::= <factor> | - <factor>
 * <factor> ::= <number> | <constant> | ( <expr> )
 */
class Parser
{
    Tokenizer _tk;
    std::unordered_map<std::string, double> &_constants;
    double _value;

    /**
     * parses <expr>
     */ 
    double expr() {
        double value = term();
        TokenType tt = _tk.token_type();
        while (tt == TokenType::Plus || tt == TokenType::Minus) {
            _tk.next_token();
            if (tt == TokenType::Plus) {
                value += term();
            }
            else {
                value -= term();
            }
            tt = _tk.token_type();
        }
        return value;
    }

    /**
     * parses <term>
     */
    double term() {
        double value = prim();
        TokenType tt = _tk.token_type();
        while (tt == TokenType::Mul || tt == TokenType::Div) {
            _tk.next_token();
            if (tt == TokenType::Mul) {
                value *= prim();
            }
            else {
                value /= prim();
            }
            tt = _tk.token_type();
        }
        return value;
    }

    /**
     * parses <prim>
     */
    double prim() {
        TokenType tt = _tk.token_type();
        if (tt == TokenType::Minus) {
            _tk.next_token();
            return -fact();
        }
        else {
            return fact();
        }
    }

    /**
     * parses <fact>
     */
    double fact() {
        TokenType tt =_tk.token_type();
        if (tt == TokenType::Number) {
            double value;
            sscanf(_tk.token_start(), "%lg", &value);
            _tk.next_token();
            return value;
        }

        if (tt == TokenType::Constant) {
            std::string constant_name(_tk.token_start(), _tk.token_end());
            const char *name_start = _tk.token_start();
            _tk.next_token();
            auto key_value = _constants.find(constant_name);
            if (key_value != _constants.end()) {
                return key_value->second;
            }
            else {
                throw ParsingError{name_start, "unknown constant name"};
            }
        }
        
        if (tt == TokenType::OpenBracket) {
            const char *open_br = _tk.token_start();
            _tk.next_token();
            double value = expr();
            if (_tk.token_type() != TokenType::CloseBracket) {
                throw ParsingError{open_br, "unmached bracket"};
            }
            _tk.next_token();
            return value;
        }

        throw ParsingError{_tk.token_start(), "number, constant or subexpression expected"};
    }

public:
    Parser(const char *str, std::unordered_map<std::string, double> &constants)
        :_tk(str), _constants(constants) {
        _value = expr();
        if (_tk.token_type() != TokenType::End) {
            throw ParsingError{_tk.token_start(), "End expected"};
        }
    }

    double value() {
        return _value;
    }
};
