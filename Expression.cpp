#include "Expression.h"
#include <iostream>
#include <vector>

using namespace std;

void Expression::inicialize_stack(stack *s)
{
    s->top = s->bottom = nullptr;
    s->size = 0;
}

void Expression::push(char c, stack *s)
{
    node_stack *token = new node_stack;

    token->val = c;
    token->next = s->top;

    s->top = token;

    if (s->bottom == nullptr)
        s->bottom = token;

    s->size++;
    return;
}
char Expression::pop(stack *s)
{
    if (s->top == nullptr)
        return ' ';

    int v = s->top->val;
    node_stack *aux = s->top;

    s->top = s->top->next;
    delete aux;

    if (s->top == nullptr)
        s->bottom = nullptr;

    s->size--;
    return v;
}

void Expression::inicialize_queue(queue *q)
{
    q->first = q->last = nullptr;
    q->size = 0;
}
void Expression::enqueue(char exp, queue *q)
{
    node_queue *token = new node_queue;
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
    node_queue *aux = q->first;

    q->first = q->first->next; // case q.1.nxt = null the expression is null
    delete aux;

    if (q->first == nullptr)
        q->last = nullptr;

    q->size--;
    return;
}

bool Expression::verify_expression(stack *raw, stack *no_space_list)
{
    node_stack *cur = raw->top;              // cursor
    node_stack *ns_cur = no_space_list->top; // no space cursor

    int parentheses = 0;

    char oprs[] = {'*', '/', '^'};
    char oprs1[] = {'+', '-'};
    char operators[] = {'+', '-', '*', '/', '^'};

    // ------ first and last number ------
    if (raw->top != nullptr)
    {
        for (char c : oprs) // prohibited: *3-2 || 3-2/

            if (raw->bottom->val == c)
                return false;

        if (isOperator(raw->top->val))
            return false;
    }
    // ------ numbers in sequence ------
    while (cur != nullptr && cur->next != nullptr) // prohibitions
    {

        if (cur->next->next != nullptr &&
            (isdigit(cur->val) && cur->next->val == ' ' && isdigit(cur->next->next->val))) // prohibited: 2 2
            return false;

        cur = cur->next;
    }
    // ------ no space stack ------
    while (ns_cur != nullptr && ns_cur->next != nullptr)
    {

        char val = ns_cur->val;
        char nextVal = ns_cur->next->val;
        // ------ char's != number or operators ------
        if (!isdigit(val) && !isOperator(val) && val != '(' && val != ')')
            return false;

        for (char c : oprs)
        {
            //------ operators in sequence ------
            if (val == c && nextVal == c) // prohibited: 3**2 || 3*/2
                return false;

            if (val == '(' && nextVal == c) // prohibited: (*3
                return false;

            for (char cc : oprs1)
            {
                if (val == c && nextVal == cc) // prohibited: 3/+2
                    return false;

                if (val == cc && nextVal == c) // prohibited: 3+/2 3++4
                    return false;
            }
        }
        // ------ parentheses control ------
        for (char c : operators)
            if (val == c && nextVal == ')') // prohibited: 3-)
                return false;

        if (isdigit(val) && nextVal == '(') // prohibited: 4(3)
            return false;

        if (val == ')' && isdigit(nextVal)) // p: (3)4
            return false;

        if (val == ')' && nextVal == '(') // p: )(
            return false;

        if (val == '(')
            parentheses++;

        if (val == ')')
        {
            parentheses--;
            if (parentheses < 0)
                return false; // p: unqual parenthesis
        }
        ns_cur = ns_cur->next;
    }

    if (ns_cur != nullptr) // checks last parentheses
    {
        if (ns_cur->val == '(') // p: 5(
            return false;

        if (ns_cur->val == ')')
        {
            parentheses--;
            if (parentheses < 0)
                return false; // p: unqual parenthesis
        }
    }

    if (parentheses != 0)
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

bool Expression::isOperator(char op)
{
    char operators[] = {'+', '-', '*', '/', '^'};
    for (char c : operators)
        if (op == c)
            return true;

    return false;
}
char Expression::returnOperator(char op)
{
    char operators[] = {'+', '-', '*', '/', '^'};

    for (char c : operators)
    {
        if (op == c)
            return c;
    }
    return ' ';
}

int Expression::get_precedence(char op)
{
    if (op == '^')
        return 3;

    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

void Expression::infix_to_posfix(stack *s, queue *q)
{
    node_stack *curS = s->top;
    stack *oprS = new stack;
    inicialize_stack(oprS);
    while (curS != nullptr)
    {
        if (isdigit(curS->val))
        {
            while (curS != nullptr && isdigit(curS->val))
            {
                enqueue(curS->val, q);
                curS = curS->next;
            }
            enqueue(' ', q);
            continue;
        }

        if (curS->val == '(')
            push(curS->val, oprS);

        else if (curS->val == ')')
        {
            while (oprS->top != nullptr && oprS->top->val != '(')
                enqueue(pop(oprS), q);

            pop(oprS);
        }

        else
        {
            string assoc = (curS->val == '^') ? "right" : "left"; // association

            while (oprS->top != nullptr && oprS->top->val != '(')
            {
                int topPrec = get_precedence(oprS->top->val);
                int tokPrec = get_precedence(curS->val);

                if ((assoc == "left" && topPrec >= tokPrec) ||
                    (assoc == "right" && topPrec > tokPrec))
                    enqueue(pop(oprS), q);

                else
                    break;
            }

            push(curS->val, oprS);
        }

        curS = curS->next;
    }
    while (oprS->top != nullptr)
        enqueue(pop(oprS), q);

    delete oprS;
}

void Expression::print(stack *s, queue *q)
{
    node_stack *curS = s->top;
    node_queue *curQ = q->first;

    vector<char> temp;

    while (curS != nullptr)
    {
        temp.push_back(curS->val);
        curS = curS->next;
    }

    // imprimir invertido
    for (int i = temp.size() - 1; i >= 0; i--)
        cout << temp[i];

    cout << "\n";


    while (curQ != nullptr)
    {
        cout << curQ->val;

        curQ = curQ->next;
    }

    cout << "\n";
}

void Expression::compile(stack *raw)
{
}