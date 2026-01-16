#include <iostream>
#include "Utils.h"
#include "Interpreter.h"
#include "Exceptions.h"
using namespace std;

int main()
{
    Interpreter interpreter;

    string expression;

    while (true)
    {
        system("clear");

        show_screen();
        getline(cin, expression);

        if (expression.empty())
        {
            print_error(EmptyExpression);
            enter_to_continue();
            continue;
        }

        interpreter.run(expression);

        enter_to_continue();
    }
}
