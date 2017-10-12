#include <cctype>
#include <string>
#include <unordered_map>
#include <errno.h>

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
    using Number = int;
    static constexpr const char *NUMBER_SCAN_FORMAT = "%d";
    
    Tokenizer _tk;
    std::unordered_map<std::string, double> &_constants;
    double _value;

    /**
     * parses <expr>
     */ 
    Number expr() {
        Number value = term();
        TokenType tt = _tk.token_type();
        while (tt == TokenType::Plus || tt == TokenType::Minus) {
            const char *op_start = _tk.token_start();
            _tk.next_token();
            if (tt == TokenType::Plus) {
                if (__builtin_add_overflow(value, term(), &value)) {
                    throw ParsingError{op_start, "add overflow"};
                }
            }
            else {
                if (__builtin_sub_overflow(value, term(), &value)) {
                    throw ParsingError{op_start, "sub overflow"};
                }
            }
            tt = _tk.token_type();
        }
        return value;
    }

    /**
     * parses <term>
     */
    Number term() {
        Number value = prim();
        TokenType tt = _tk.token_type();
        while (tt == TokenType::Mul || tt == TokenType::Div) {
            const char *op_start = _tk.token_start();
            _tk.next_token();
            if (tt == TokenType::Mul) {
                if (__builtin_mul_overflow(value, prim(), &value)) {
                    throw ParsingError{op_start, "mul overflow"};
                }
            }
            else {
                // division cannot overflow
                Number prim_value = prim();
                if (prim_value) {
                    value /= prim_value;
                }
                else {
                    throw ParsingError{op_start, "division by 0 detected"};
                }
            }
            tt = _tk.token_type();
        }
        return value;
    }

    /**
     * parses <prim>
     */
    Number prim() {
        TokenType tt = _tk.token_type();
        if (tt == TokenType::Minus) {
            const char *op_start = _tk.token_start();
            Number neg_value;
            _tk.next_token();
            if (__builtin_sub_overflow(0, fact(), &neg_value)) {
                throw ParsingError{op_start, "unary minus overflow"};
            }
            return neg_value;
        }
        else {
            return fact();
        }
    }

    /**
     * parses <fact>
     */
    Number fact() {
        TokenType tt =_tk.token_type();
        if (tt == TokenType::Number) {
            Number value;
            errno = 0;
            sscanf(_tk.token_start(), NUMBER_SCAN_FORMAT, &value);
            if (errno == ERANGE) {
                throw ParsingError{_tk.token_start(), "value out of range"};
            }
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
                throw ParsingError{name_start, "unknown constant"};
            }
        }
        
        if (tt == TokenType::OpenBracket) {
            const char *open_br = _tk.token_start();
            _tk.next_token();
            Number value = expr();
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

    Number value() {
        return _value;
    }
};
