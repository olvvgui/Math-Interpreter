#include <iostream>
#include "Expression.h"
#include "Token.h"
#include "Utils.h"
using namespace std;

int main()
{
    Expression exp;

    string expression;

    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string BOLD = "\033[1m";
    const string RESET = "\033[0m";

    while (true)
    {
        // system("clear");

        cout << BOLD << "Example of a valid expression:"
             << RESET << endl;

        cout << GREEN << "(-4) + 3 * 5^4 * (3/4)\n"
             << RESET << endl;

        cout << RED << "Type your Expression:\n"
             << RESET << endl;

        getline(cin, expression);
        if (expression.empty())
        {
            cout << "Empty Expression" << endl;
            enter_to_continue();
            continue;
        }

        vector<Token> tokens = tokenize(expression);
        print_tokens(tokens);

        if (!verify_expression(tokens))
        {
            cout << RED << "Unvalid Expression" << RESET << endl;
            enter_to_continue();
            continue;
        }

        exp.compile(tokens);

        enter_to_continue();
    }
}
