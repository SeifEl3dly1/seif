#include <iostream>
using namespace std;

// Character classes used to categorize input characters
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define EOF_TOKEN -1

// Token codes for different types of lexemes
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

// Global declarations
char lexeme[100];
char nextChar;
int charClass;
int lexLen;
int token;
int nextToken;

// Adds current character to lexeme array
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

// Reads the next character and classifies it
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

// Skips whitespace characters
void getNonBlank()
{
    while (isspace(nextChar)) {
        getChar();
    }
}

// Determines token for single-character operators and parentheses
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

// Lexical analyzer that returns tokens and builds lexemes
int lex() {
    // Initialize lexeme length
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
    // Start the lexical analysis
    getChar();
    do {
        lex();
    } while (nextToken != EOF_TOKEN);

    return 0;
}
