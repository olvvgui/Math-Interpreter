#include "Exceptions.h"

void print_error(ErrorCode code)
{

    switch (code)
    {
    case InvalidToken:
        std::cerr << RED << "INVALID TOKEN" << RESET
                  << " ERROR!!!\n";
        break;

    case UnexpectedToken:
        std::cerr << RED << "UNEXPECTED TOKEN" << RESET
                  << " ERROR!!!\n";
        break;

    case DivisionByZero:
        std::cerr << RED << "DIVISION BY ZERO" << RESET
                  << " ERROR!!!\n";
        break;

    case UnmatchedParenthesis:
        std::cerr << RED << "UNMATCHED PARENTHESIS" << RESET
                  << " ERROR!!!\n";
        break;

    case ParenthesisMisuse:
        std::cerr << RED << "PARENTHESIS MISUSE" << RESET
                  << " ERROR!!!\n";
        break;

    case EmptyExpression:
        std::cerr << RED << "EMPTY EXPRESSION" << RESET
                  << " ERROR!!!\n";
        break;

    case ConsecutiveOperators:
        std::cerr << RED << "CONSECUTIVE OPERATORS" << RESET
                  << " ERROR!!!\n";
        break;
    case ConsecutiveNumbers:
        std::cerr << RED << "CONSECUTIVE NUMBERS" << RESET
                  << " ERROR!!!\n";
        break;

    case SyntaxError:
        std::cerr << RED << "SYNTAX ERROR" << RESET
                  << " ERROR!!!\n";
        break;
    }
}
