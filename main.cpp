#include <iostream>
#include "Expression.h"
using namespace std;

int main()
{
    Expression exp;
    Expression::stack raw_stack;
    Expression::stack ns_stack; // no space stack
    exp.inicialize_stack(&raw_stack);
    exp.inicialize_stack(&ns_stack);

    Expression::queue q;
    exp.inicialize_queue(&q);

    // system("clear");

    cout << "Example of a valid expression\n(-4) + 3 * 5^4 (3/4)\n\n";
    cout << "Type your Expression:\n";

    while (true)
    {
        char c = cin.get();

        if (c == '\n')
            break;

        exp.push(c, &raw_stack);

        if (c != ' ')
            exp.push(c, &ns_stack);
    }
    printf("%s\n", exp.verify_expression(&raw_stack, &ns_stack) ? "deu certo" : "false");

    exp.infix_to_posfix(&raw_stack, &q);

    exp.print(&raw_stack, &q);
}
