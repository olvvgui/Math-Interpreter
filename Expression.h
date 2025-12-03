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

    typedef struct
    {
        node *first;
        node *last;
        int size;
    } queue;

    void inicialize_stack(stack *s);
    void push(char exp, stack *s);
    void pop(stack *s);

    void inicialize_queue(queue *q);
    void enqueue(char exp, queue *q);
    void dequeue(queue *q);

    bool verify_expression(stack *s, stack *no_space_stack);
    void infix_to_posfix(stack *s, queue *q);
    char isOperator(char op);
    void compile(stack *raw);
};

#endif