#include <iostream>
using namespace std;

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define EOF_TOKEN -1

#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define SEMECOLON_OP 27
 char lexeme[100];
char nextChar;
int charClass;
int lexLen;
int token;
int nextToken;
void addChar()
{
    if (lexLen < 98)
    {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    } else {
     cout << "Error - lexeme is too long" << endl;
    }
}
void getChar()
{
    if (cin.get(nextChar)) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    } else {
        charClass = EOF_TOKEN;
    }
}
void getNonBlank()
{
    while (isspace(nextChar)) {
        getChar();
    }
}
int lookup(char ch)
{
    switch (ch) {
        case '(': addChar(); return LEFT_PAREN;
        case ')': addChar(); return RIGHT_PAREN;
        case '+': addChar(); return ADD_OP;
        case '-': addChar(); return SUB_OP;
        case '*': addChar(); return MULT_OP;
        case '/': addChar(); return DIV_OP;
        case '=': addChar(); return ASSIGN_OP;
        case ';': addChar(); return SEMECOLON_OP;
        default: addChar(); return EOF_TOKEN;
 }
}
int lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
        }
            nextToken = INT_LIT;
            break;
        case UNKNOWN:
            nextToken = lookup(nextChar);
            getChar();
            break;
        case EOF_TOKEN:
            nextToken = EOF_TOKEN;
        break;
    }
    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}
int main() {
    getChar();
    do {
        lex();
    } while (nextToken != EOF_TOKEN);

    return 0;
}
