#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <vector>
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
        node *first;
        node *last;
        int size;
    } queue;

    typedef struct node_stack
    {
        char val;
        struct node_stack *next;
    } node_stack;

    typedef struct
    {
        node_stack *top;
        int size;
    } stack;

    void inicialize_queue(queue *q);
    void enqueue(char exp, queue *q);
    void dequeue(queue *q);

    void inicialize_stack(stack *s);
    void push(char exp, stack *s);
    char pop(stack *s);

    bool isOperator(char op);
    char returnOperator(char op);
    int get_precedence(char op);
    void print(queue *ifx, queue *pfx);

    bool verify_expression(queue *s, queue *no_space_queue);
    void infix_to_posfix(queue *ifx, queue *pfx);
    void compile(queue *pfx);
};

#endif