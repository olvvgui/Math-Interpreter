#include "Expression.h"

using namespace std;

/* ===================== */
/*         QUEUE        */
/* ===================== */

void Expression::inicialize_queue(queue *q)
{
    q->first = q->last = nullptr;
}

void Expression::enqueue(queue *q, Token t)
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

bool Expression::dequeue(queue *q, Token &out)
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

void Expression::inicialize_stack(stack *s)
{
    s->top = nullptr;
    s->size = 0;
}

void Expression::push(char c, stack *s)
{
    node_stack *token = new node_stack;

    token->val = c;
    token->next = s->top;
    s->top = token;
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
    s->size--;
    return v;
}

/* ===================== */
/*      TREE & LEAF      */
/* ===================== */
void Expression::inicialize_tree(tree *t)
{
    t->top = -1;
}

void Expression::push_tree(tree *t, leaf *n)
{
    if (t->top >= 100 - 1)
    {
        return;
    }

    t->top++;
    t->data[t->top] = n;
    return;
}

Expression::leaf *Expression::pop_tree(tree *t)
{
    if (t->top < 0)
        return nullptr;
    return t->data[t->top--];
}

Expression::leaf *Expression::new_leaf(Token &t)
{
    leaf *l = new leaf;
    l->tok = t;
    l->left = l->right = nullptr;
    return l;
}

/* ===================== */
/*      INTERPRETER      */
/* ===================== */

void Expression::tokens_in_queue(vector<Token> &tokens, queue *ifx)
{
    for (Token &t : tokens)
    {
        enqueue(ifx, t);
    }
}

void Expression::infix_to_posfix(queue *ifx, queue *pfx)
{
    node *cur = ifx->first;
    stack *oprS = new stack;
    inicialize_stack(oprS);
    while (cur != nullptr)
    {
        Token &tok = cur->tok;
        if (tok.type == NUMBER)
        {
            enqueue(pfx, tok);
        }

        else if (tok.type == LPAREN)
            push(tok.op, oprS);

        else if (tok.type == RPAREN)
        {
            while (oprS->top != nullptr && oprS->top->val != '(')
            {
                enqueue(pfx, OperatorToken(pop(oprS)));
            }
            if (oprS->top == nullptr)
                return; // syntax error

            pop(oprS);
        }

        else
        {
            bool isValidPosition = cur == ifx->first ||
                                   (cur->prev && isOperator(cur->prev->tok.op)) ||
                                   (cur->prev && cur->prev->tok.type == LPAREN);

            char op = tok.op;
            if (isValidPosition && op == '-')
                op = '~';

            bool right_assoc = (op == '^' || op == '~'); // association

            while (oprS->top != nullptr && oprS->top->val != '(')
            {
                int firstPrec = get_precedence(oprS->top->val);
                int tokPrec = get_precedence(op);

                if ((!right_assoc && firstPrec >= tokPrec) ||
                    (right_assoc && firstPrec > tokPrec))

                    enqueue(pfx, OperatorToken(pop(oprS)));

                else
                    break;
            }

            push(op, oprS);
        }

        cur = cur->next;
    }
    while (oprS->top != nullptr)
    {
        if (oprS->top->val == '(')
            return;
        enqueue(pfx, OperatorToken(pop(oprS)));
    }

    delete oprS;
}

Expression::leaf *Expression::posfix_to_tree(queue *pfx)
{
    tree t;
    inicialize_tree(&t);
    node *cur = pfx->first;

    while (cur != nullptr)
    {

        Token &tok = cur->tok;
        if (tok.type == NUMBER)
            cout << "Lendo: [" << tok.val << "]" << endl;
        else
            cout << "Lendo: [" << tok.op << "]" << endl;

        if (tok.type == NUMBER)
        {
            push_tree(&t, new_leaf(tok));
            cur = cur->next;
            continue;
        }

        else if (tok.val == '~')
        {

            leaf *right = pop_tree(&t);
            leaf *root = new_leaf(tok);
            if (right == nullptr)
                return nullptr;
            root->right = right;
            root->left = nullptr;
            push_tree(&t, root);
        }

        else
        {
            leaf *right = pop_tree(&t);
            leaf *left = pop_tree(&t);
            if (right == nullptr || left == nullptr)
                return nullptr;
            leaf *root = new_leaf(tok);
            root->right = right;
            root->left = left;
            push_tree(&t, root);
        }

        cur = cur->next;
    }
    return pop_tree(&t);
}

double Expression::evaluate(leaf *root)
{
    Token &tok = root->tok;
    if (tok.type == NUMBER)
        return tok.val;

    if (tok.val == '~')
    {
        double right = evaluate(root->right);
        return -right;
    }

    double left = evaluate(root->left);
    double right = evaluate(root->right);

    switch (tok.op)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        return left / right;
    case '^':
        return pow(left, right);
    }
    return 0;
}

double Expression::compile(vector<Token> &tokens)
{
    const string GREEN = "\033[32m";
    const string BOLD = "\033[1m";
    const string RESET = "\033[0m";

    queue q;
    queue posfix;
    tree t;
    inicialize_queue(&q);
    inicialize_queue(&posfix);
    inicialize_tree(&t);

    tokens_in_queue(tokens, &q);

    infix_to_posfix(&q, &posfix);

    leaf *l = posfix_to_tree(&posfix);

    cout << BOLD << "\nResult: " << RESET;

    cout << GREEN << evaluate(l) << RESET << endl;

    return evaluate(l);
}