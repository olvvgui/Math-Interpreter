#include "Utils.h"

bool isOperator(char op)
{
    char operators[] = {'+', '-', '*', '/', '^', '~'};
    for (char c : operators)
        if (op == c)
            return true;

    return false;
}
char wreturnOperator(char op)
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
    if (op == '^')
        return 4; // unary operator
    if (op == '~')
        return 3;

    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}
void hide_cursor()
{
    std::cout << "\033[?25l";
    std::cout.flush();
}

void show_cursor()
{
    std::cout << "\033[?25h";
    std::cout.flush();
}
void enter_to_continue()
{
    hide_cursor();
    cout << RED << "\nPress enter to continue" << RESET << endl;

    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    show_cursor();
}

void show_screen()
{

    cout << BOLD << "Example of a valid expression:"
         << RESET << endl;

    cout << GREEN << "(-4) + 3 * 5^4 * (3/4)\n"
         << RESET << endl;

    cout << RED << "Type your Expression:\n"
         << RESET << endl;
}
