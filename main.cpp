#include <iostream>
#include <limits>
#include "Expression.h"
using namespace std;

int main()
{
    Expression exp;
    Expression::queue raw_queue;
    Expression::queue ns_queue; // no space queue
    Expression::queue posfix;
    Expression::tree tree;

    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string BOLD = "\033[1m";
    const string RESET = "\033[0m";

    while (true)
    {
        // system("clear");

        exp.inicialize_queue(&raw_queue);
        exp.inicialize_queue(&ns_queue);
        exp.inicialize_queue(&posfix);
        exp.inicialize_tree(&tree);

        cout << BOLD << "Example of a valid expression:"
             << RESET << endl;

        cout << GREEN << "(-4) + 3 * 5^4 * (3/4)\n"
             << RESET << endl;

        cout << RED << "Type your Expression:\n"
             << RESET << endl;

        while (true)
        {
            char c = cin.get();

            if (c == '\n')
                break;

            exp.enqueue(c, &raw_queue);

            if (c != ' ')
                exp.enqueue(c, &ns_queue);
        }
        if (!exp.verify_expression(&raw_queue, &ns_queue))
        {
            cout << "false";
            return 1;
        }

        exp.infix_to_posfix(&ns_queue, &posfix);

        exp.print(&ns_queue, &posfix);

        Expression::leaf *leaf = exp.posfix_to_tree(&posfix);
        cout << BOLD << "\nResult: " << RESET;
        cout << GREEN << exp.compile(leaf) << RESET << endl;

        cout << RED << "\nPress enter to continue" << RESET << endl;

        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }
}
