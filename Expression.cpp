#include "Expression.h"
#include <iostream>
using namespace std;

void Expression::inicialize(stack *p)
{
    p->top = p->bottom = nullptr;
    p->size = 0;
}

void Expression::push(char c, stack *p)
{
    node *token = new node;

    token->val = c;
    token->next = p->top;

    p->top = token;

    if (p->bottom == nullptr)
        p->bottom = token;

    p->size++;
    return;
}

bool Expression::verify_expression(stack *raw, stack *no_space_list)
{
    node *cur = raw->top;              // cursor
    node *ns_cur = no_space_list->top; // no space cursor

    int stack = 0;

    char oprs[] = {'*', '/', '^'};
    char oprs1[] = {'+', '-'};
    char operators[] = {'+', '-', '*', '/', '^'};
    if (raw->bottom && raw->top != nullptr)
    {
        for (char c : operators) // prohibited: *3-2 || 3-2/
        {
            if (raw->bottom->val == c)
                return false;

            if (raw->top->val == c)
                return false;
        }
    }
    while (cur != nullptr && cur->next != nullptr) // prohibitions
    {

        if (cur->next->next != nullptr &&
            (isdigit(cur->val) && cur->next->val == ' ' && isdigit(cur->next->next->val))) // prohibited: 2 2
            return false;

        cur = cur->next;
    }
    while (ns_cur != nullptr && ns_cur->next != nullptr)
    {

        for (char c : operators)
            if (!isdigit(ns_cur->val) || ns_cur->val != c)
                return false;

        for (char c : oprs)
        {
            if (ns_cur->val == c && ns_cur->next->val == c) // prohibited: 3**2 || 3*/2
                return false;

            if (ns_cur->val == '(' && ns_cur->next->val == c) // prohibited: (*3
                return false;

            for (char cc : oprs1)
            {
                if (ns_cur->val == c && ns_cur->next->val == cc) // prohibited: 3/+2
                    return false;

                if (ns_cur->val == cc && ns_cur->next->val == c) // prohibited: 3+/2 3++4
                    return false;
            }
        }
        for (char c : operators)
            if (ns_cur->val == c && ns_cur->next->val == ')') // prohibited: 3-)
                return false;

        if (isdigit(ns_cur->val) && ns_cur->next->val == '(') // prohibited: 4(3)
            return false;

        if (ns_cur->val == ')' && isdigit(ns_cur->next->val))
            return false;

        if (ns_cur->val == '(')
            stack++;

        if (ns_cur->val == ')')
        {
            stack--;
            if (stack < 0)
                return false;
        }
        ns_cur = ns_cur->next;
    }
    if (stack != 0)
        return false;

    return true;

    // prohibitions stack
    // prohibited: *3-2 || 3-2/
    // prohibited: 3**2 || 3*/2
    // prohibited: (*3
    // prohibited: 3/+2
    // prohibited: 3+/2 || 3 ++ 4
    // prohibited: 3-)
    // prohibited: 4(3)
}

char Expression::isOperator(char op)
{
    char operators[] = {'+', '-', '*', '/', '^'};

    for (char c : operators)
    {
        if (op == c)
            return c;
    }
}
void Expression::compile(stack *raw)
{

}