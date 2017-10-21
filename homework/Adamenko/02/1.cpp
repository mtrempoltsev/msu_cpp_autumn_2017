#include <iostream>

#define NaN  -1
#define MIN   1 
#define SUM   2
#define MUL   3
#define DIV   4
#define NUM   5
#define endl -2
using namespace std;


int get_token(const char *&S) {   
    while(char c = *S++){
        if (c == '*') return MUL;
        if (c == '/') return DIV;
        if (c == '-') return MIN;
        if (c == '+') return SUM;
        if (c == ' ') continue;
        if (c >= '0' && c <= '9'){
            for (char c = *S; c >= '0' && c <= '9';){ 
                S++;
                c = *S;
            }
            return NUM;
        }

        return NaN;
    }
    return endl;
}

int prior1(const char *&S, int &token, const char *&prev) {
    token = get_token(S);
    switch (token){        
        case NUM:{
            int d = atoi(prev);
            token = get_token(S);
            prev = S;

            if (token == NaN) 
                throw -1; 

            return d;
        }
        case MIN:{
            int d = prior1(S, token, prev);
            return d;
        }
        default: 
            throw -1;
    }
}

int prior2(const char *&S, int &token, const char *&prev) {
    int res = prior1(S, token, prev); 
    bool cont = true;
    while(cont){
        switch (token){
            case MUL:{
                res *= prior1(S, token, prev);
                continue;
            }
            case DIV:{
                int znamen = prior1(S, token, prev);
                if (znamen == 0) 
                    throw -2;
                res /= znamen;
                continue;
            }
            default: 
                cont = false;
        }
    }
    return res;
}

int calculate(const char *&S, int &token, const char *&prev) {
    int res = prior2(S, token, prev); 
    bool cont = true;
    while(cont){
        switch (token){
            case SUM:{
                res += prior2(S, token, prev);
                continue;    
            }
            case MIN:{
                res -= prior2(S, token, prev);
                continue;
            }
            default: 
                cont = false;
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    try{
        const char* S    = argv[1];
        const char* prev = S;
        int token        = get_token(S);
        S                = prev;
        int res          = calculate(S, token, prev);
        std::cout << res << "\n";
    }
    catch(int e){
        std::cout << "Not correct input\n";
        return 1;
    }

    return 0;
}