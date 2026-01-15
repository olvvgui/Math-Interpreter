#ifndef DATAESTRUCTURES_H
#define DATAESTRUCTURES_H

#include <iostream>
#include <cmath>

#include "Token.h"
#include "Utils.h"

using namespace std;

/* ========QUEUE======== */

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

/* --------------------- */

/* ========STACK======== */

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

/* --------------------- */

/* =====TREE & LEAF===== */

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

/* --------------------- */

/* ========QUEUE======== */

void inicialize_queue(queue *q);
void enqueue(queue *q, Token t);
bool dequeue(queue *q, Token &out);

/* ========STACK======== */
void inicialize_stack(stack *s);
void push(char c, stack *s);
char pop(stack *s);

/* =====TREE & LEAF===== */
void inicialize_tree(tree *t);
void push_tree(tree *t, leaf *n);
leaf *pop_tree(tree *t);
leaf *new_leaf(Token &t);

#endif