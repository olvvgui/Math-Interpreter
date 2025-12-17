#include "Utils.h"

bool isOperator(char op)
{
    char operators[] = {'+', '-', '*', '/', '^', '~'};
    for (char c : operators)
        if (op == c)
            return true;

    return false;
}
char returnOperator(char op)
{
    char operators[] = {'+', '-', '*', '/', '^'};

    for (char c : operators)
    {
        if (op == c)
            return c;
    }
    return ' ';
}

int get_precedence(char op)
{
    if (op == '~')
        return 4; // unary operator
    if (op == '^')
        return 3;

    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}
void enter_to_continue()
{

    const string RED = "\033[31m";
    const string RESET = "\033[0m";
    cout << RED << "\nPress enter to continue" << RESET << endl;

    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
}