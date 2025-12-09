#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <vector>
using namespace std;

class Expression
{

public:
    typedef struct node_stack
    {
        char val;
        struct node_stack *next;
    } node_stack;

    typedef struct
    {
        node_stack *top;
        node_stack *bottom;
        int size;
    } stack;

    typedef struct node_queue
    {
        string val;
        struct node_queue *next;
    } node_queue;

    typedef struct
    {
        node_queue *first;
        node_queue *last;
        int size;
    } queue;

    void inicialize_stack(stack *s);
    void push(char exp, stack *s);
    char pop(stack *s);

    void inicialize_queue(queue *q);
    void enqueue(char exp, queue *q);
    void dequeue(queue *q);

    bool isOperator(char op);
    char returnOperator(char op);
    int get_precedence(char op);
    void print(stack *s, queue *q);

    bool verify_expression(stack *s, stack *no_space_stack);
    void infix_to_posfix(stack *s, queue *q);
    void compile(stack *raw);
};

#endif