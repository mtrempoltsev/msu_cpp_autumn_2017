#include <iostream>
#include <string>
#define INCORRECT_PARAMS 1 // Ошибка: некорректное кол-во аргументов
#define INCORRECT_INPUT 2 // Ошибка: некорректное арифметическое выражение
#define ZERO_DIVISION 3 // Ошибка: деление на 0
#define OK 0 

enum class Token {
    Invalid,
    Minus,
    Plus,
    Mul,
    Div,
    Number,
    End
};

/* Рекурсивная функция для разбиения выражения на слогаемые (или вычитаемое и частное), 
 * либо на число, если text является простым выражением, 
 * например, text = "123"
 */
double expr(const char*& text);
/* Рекурсивная функция для разбиения выражения на множители (или делимое и делитель), 
 * либо на число, если text является простым выражением, 
 * например, text = "123".
 * Аргумент типа size_t необходим для подсчёта числа знаков '/' в терме,
 * Т.к. возникаются трудности при вычислении такого выражения: 2 * 3 / 4
 * Алгоритм его воспринимает как: 2 * (3 / 4), 
 * что не является корректным результатом исходного выражения.
 * Поэтому необходимо инвертировать каждый знак '*', вложенный в '/', 
 * если степень вложенности нечётная.
 */
double term(const char*&, size_t = 0);
// Рекурсивная функция, преобразующая текст в целочисленное значение
double prim(const char*&);

// Функция для получения текущего токена из входной последовательности
Token getToken(const char*& text) {
    while (const auto ch = *text++) {
        switch (ch) {
            case ' ': continue;
            case '+': return Token::Plus;
            case '-': return Token::Minus;
            case '*': return Token::Mul;
            case '/': return Token::Div;            
        }

        if (ch >= '0' && ch <= '9') {
            return Token::Number;
        }
        else return Token::Invalid;
    }
    return Token::End;
}

double expr(const char*& text) {
    auto leftOperand = term(text);
    auto token = getToken(text);
    if (Token::End != token) {
        return Token::Plus != token ? leftOperand - expr(text) : leftOperand + expr(text);
    }
    else return leftOperand;
}

double term(const char*& text, size_t cntEnter) {
    auto leftOperand = prim(text);
    auto token = getToken(text);
    if (Token::Mul == token || Token::Div == token) {
        /* Проверка на кол-во "вложенности" делений
         * Если бы не было данной проверки, то программа воспринимала бы такое выражение "2 / 3 * 4"
         * Как "2 / (3 * 4)" = 1 / 6, что != 8 / 3
         * Для борбы с этой проблемой было решено подсчитывать степень вложенности делений
         * Т.е. все знаки ('*' или '/'), которые внутри '/' будут инвертироваться
         */
        if ((cntEnter & 1) == 0) { // Проверка на нечётность
            return Token::Mul != token ? leftOperand / term(text, cntEnter + 1) : leftOperand * term(text, cntEnter);
        }
        else {
            return Token::Mul != token ? leftOperand * term(text, cntEnter) : leftOperand / term(text, cntEnter + 1);
        }
    }
    else {
        --text; // Когда getToken равняется '+' или '-', нам необходимо вернуть этот токен назад в text
        return leftOperand;
    }
}

double prim(const char*& text) {
    auto token = getToken(text);
    
    if (Token::Number == token) {
        int val = 0;
        /* Возвращаем символ, являющийся цифрой, во входную последовательность, 
         * чтобы корректно преобразовать строку в число.
         */
        --text;
        // Преобазование строки в целочисленный тип
        for (auto ch = *text; ch >= '0' && ch <= '9'; ) {
            val = val * 10 + ch - '0';
            ch = *++text;
        }
        return val;
    }
    else return -prim(text);
}

int checkInput(const char* text) {
    char prevCh = *text++; // токен, считанный на предыдущей итерации
    size_t cntOperators = 0; // кол-во операторов, используемых послед-но
    while (prevCh) {
        if (prevCh != ' ')
            break;
        prevCh = *text++;
    }
    if ((prevCh >= '0' && prevCh <= '9') || prevCh == '-') {
        if (prevCh == '-')
            cntOperators++;
        while (const auto ch = *text++) {            
            switch (ch) {
                case ' ': continue;
                case '-': 
                    if ((prevCh >= '0' && prevCh <= '9') || cntOperators <= 1) {
                        prevCh = ch;
                        cntOperators++;
                        continue;
                    }
                    else return INCORRECT_INPUT;
                case '+':                     
                case '*':
                case '/':
                    if (prevCh >= '0' && prevCh <= '9') {
                        prevCh = ch;
                        cntOperators++;
                        continue;
                    }
                    else return INCORRECT_INPUT;
                case '0':
                    if (prevCh == '/')
                        return ZERO_DIVISION;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if ((prevCh >= '0' && prevCh <= '9') || cntOperators > 0) {
                        cntOperators = 0;
                        prevCh = ch;
                        continue;
                    }
                    else return INCORRECT_INPUT;
                default:
                    return INCORRECT_INPUT;
            }
        }
        if (cntOperators > 0)
            return INCORRECT_INPUT;
    }
    else return INCORRECT_INPUT;
    return OK;
}

int main(int argc, char* argv[]) {
    if (argc != 2)
        return INCORRECT_PARAMS;
    auto checkCode = checkInput(argv[1]);
    if (checkCode != OK)
        return checkCode;
    // Оператор деления - вещественный
    const char* text = argv[1];
    std::cout << expr(text) << std::endl;
    return 0;
}