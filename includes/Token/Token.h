#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <vector>
#include "Utils.h"
#include "Exceptions.h"

using namespace std;

enum TokenType
{
    NUMBER,
    OPERATOR,
    BINARY_OPERATOR,
    UNARY_OPERATOR,
    LPAREN,
    RPAREN,
};

struct Token
{
    TokenType type;
    double val;
    char op;
};

Token NumberToken(double val);
Token OperatorToken(char op);
vector<Token> tokenize(string &exp);
void print_tokens(vector<Token> &tokens);

#endif