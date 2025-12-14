#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <cmath>
using namespace std;

class Expression
{

public:
    typedef struct node
    {
        char val;
        struct node *prev;
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

    typedef struct leaf
    {
        char val;
        double val_number;
        bool isNumber;
        struct leaf *left;
        struct leaf *right;

    } leaf;

    typedef struct
    {
        leaf *data[100];
        int top;
    } tree;

    void inicialize_queue(queue *q);
    void enqueue(char exp, queue *q);
    void dequeue(queue *q);

    void inicialize_stack(stack *s);
    void push(char exp, stack *s);
    char pop(stack *s);

    void inicialize_tree(tree *t);
    void push_tree(tree *t, leaf *n);
    leaf *pop_tree(tree *t);
    leaf *new_leaf(char val);
    leaf *new_leaf_number(double val);

    bool isOperator(char op);
    char returnOperator(char op);
    int get_precedence(char op);
    void print(queue *ifx, queue *pfx);

    double parse_char(node* &digit);

    bool verify_expression(queue *s, queue *no_space_queue);
    void infix_to_posfix(queue *ifx, queue *pfx);
    leaf *posfix_to_tree(queue *pfx);
    double compile(leaf *l);
};

#endif