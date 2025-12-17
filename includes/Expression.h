#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <cmath>

#include "Token.h"
#include "Utils.h"

using namespace std;
class Expression
{

private:
    typedef struct node
    {
        Token tok;
        struct node *prev;
        struct node *next;
    } node;

    typedef struct
    {
        node *first;
        node *last;
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
        Token tok;
        struct leaf *left;
        struct leaf *right;

    } leaf;

    typedef struct
    {
        leaf *data[100];
        int top;
    } tree;

    void inicialize_queue(queue *q);
    void enqueue(queue *q, Token t);
    bool dequeue(queue *q, Token &out);

    void inicialize_stack(stack *s);
    void push(char c, stack *s);
    char pop(stack *s);

    void inicialize_tree(tree *t);
    void push_tree(tree *t, leaf *n);
    leaf *pop_tree(tree *t);
    leaf *new_leaf(Token &t);

    void tokens_in_queue(vector<Token> &tokens, queue *ifx);
    void infix_to_posfix(queue *ifx, queue *pfx);
    leaf *posfix_to_tree(queue *pfx);
    double evaluate(leaf *l);

public:
    double compile(vector<Token> &tokens);
};

#endif