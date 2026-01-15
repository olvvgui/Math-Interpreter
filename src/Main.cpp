#include <iostream>
#include "DataStructures.h"
#include "Token.h"
#include "Utils.h"
#include "Interpreter.h"
#include "Exceptions.h"
using namespace std;

int main()
{

    /*TODO:
arrumar o negativo (-4)
tentar fazer uma tela bonita com html e css
separar util matematico de tela
    */
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
