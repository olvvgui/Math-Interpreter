#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include "Utils.h"
using namespace std;

enum ErrorCode
{
    InvalidToken,
    UnexpectedToken,
    DivisionByZero,
    UnmatchedParenthesis,
    ParenthesisMisuse,
    EmptyExpression,
    ConsecutiveOperators,
    ConsecutiveNumbers,
    SyntaxError
};

void print_error(ErrorCode code);

#endif