#include "Expression.h"
#include <iostream>
using namespace std;

void Expression::inicialize_stack(stack *s)
{
    s->top = s->bottom = nullptr;
    s->size = 0;
}

void Expression::push(char c, stack *s)
{
    node *token = new node;

    token->val = c;
    token->next = s->top;

    s->top = token;

    if (s->bottom == nullptr)
        s->bottom = token;

    s->size++;
    return;
}
void Expression::pop(stack *s)
{
    if (s->top == nullptr)
        return;

    node *aux = s->top;

    s->top = s->top->next;
    delete aux;

    if (s->top == nullptr)
        s->bottom = nullptr;

    s->size--;
    return;
}

void Expression::inicialize_queue(queue *q)
{
    q->first = q->last = nullptr;
    q->size = 0;
}
void Expression::enqueue(char exp, queue *q)
{
    node *token = new node;
    token->val = exp;
    token->next = nullptr;

    if (q->first == nullptr)
    {
        q->first = token;
        q->last = token;
    }
    else
    {
        q->last->next = token;
        q->last = token;
    }
    q->size++;
    return;
}

void Expression::dequeue(queue *q)
{

    if (q->first == nullptr)
        return;
    node *aux = q->first;

    q->first = q->first->next; // case q.1.nxt = null the expression is null
    delete aux;

    if (q->first == nullptr)
        q->last = nullptr;

    q->size--;
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

void Expression::infix_to_posfix(stack *s, queue *q)
{
    
}

void Expression::compile(stack *raw)
{
}