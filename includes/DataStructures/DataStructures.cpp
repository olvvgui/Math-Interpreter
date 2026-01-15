#include "DataStructures.h"

using namespace std;

/* ===================== */
/*         QUEUE        */
/* ===================== */

void inicialize_queue(queue *q)
{
    q->first = q->last = nullptr;
}

void enqueue(queue *q, Token t)
{
    node *temp = new node;
    temp->tok = t;
    temp->next = nullptr;
    temp->prev = q->last;

    if (q->first == nullptr)
    {
        q->first = temp;
        q->last = temp;
    }
    else
    {
        q->last->next = temp;
        q->last = temp;
    }
    return;
}

bool dequeue(queue *q, Token &out)
{

    if (q->first == nullptr)
        return false;
    node *aux = q->first;

    q->first = q->first->next; // case q.1.nxt = null the expression is null
    out = aux->tok;
    delete aux;

    if (q->first == nullptr)
        q->last = nullptr;

    return true;
}

/* ===================== */
/*        STACKS         */
/* ===================== */

void inicialize_stack(stack *s)
{
    s->top = nullptr;
    s->size = 0;
}

void push(char c, stack *s)
{
    node_stack *token = new node_stack;

    token->val = c;
    token->next = s->top;
    s->top = token;
    s->size++;
    return;
}

char pop(stack *s)
{
    if (s->top == nullptr)
        return ' ';

    int v = s->top->val;
    node_stack *aux = s->top;

    s->top = s->top->next;
    delete aux;
    s->size--;
    return v;
}

/* ===================== */
/*      TREE & LEAF      */
/* ===================== */
void inicialize_tree(tree *t)
{
    t->top = -1;
}

void push_tree(tree *t, leaf *n)
{
    if (t->top >= 100 - 1)
    {
        return;
    }

    t->top++;
    t->data[t->top] = n;
    return;
}

leaf *pop_tree(tree *t)
{
    if (t->top < 0)
        return nullptr;
    return t->data[t->top--];
}

leaf *new_leaf(Token &t)
{
    leaf *l = new leaf;
    l->tok = t;
    l->left = l->right = nullptr;
    return l;
}

