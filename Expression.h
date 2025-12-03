#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
using namespace std;

class Expression
{

public:
    typedef struct node
    {
        char val;
        struct node *next;
    } node;

    typedef struct
    {
        node *top;
        node *bottom;
        int size;
    } stack;

    void inicialize(stack *p);
    void push(char exp, stack *p);
    void compile(stack *raw);
    bool verify_expression(stack *p, stack *no_space_stack);

    char isOperator(char op);
};

#endif