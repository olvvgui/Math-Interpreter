#include "Expression.h"
#include <iostream>
#include <cmath>

using namespace std;

void Expression::inicialize_queue(queue *q)
{
    q->first = q->last = nullptr;
    q->size = 0;
}
void Expression::enqueue(char exp, queue *q)
{
    node *token = new node;
    token->val = exp;
    token->next = nullptr;
    token->prev = q->last;

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
    node *aux = q->first;

    q->first = q->first->next; // case q.1.nxt = null the expression is null
    delete aux;

    if (q->first == nullptr)
        q->last = nullptr;

    q->size--;
    return;
}

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
Expression::leaf *Expression::pop_tree(Expression::tree *t)
{
    if (t->top < 0)
        return nullptr;
    return t->data[t->top--];
}
Expression::leaf *Expression::new_leaf(char val)
{
    leaf *l = new leaf;
    l->val = val;
    l->left = l->right = nullptr;
    l->isNumber = false;
    return l;
}

Expression::leaf *Expression::new_leaf_number(double val)
{
    leaf *l = new leaf;
    l->val_number = val;
    l->left = l->right = nullptr;
    l->isNumber = true;
    return l;
}

bool Expression::verify_expression(queue *raw, queue *no_space_queue)
{
    node *cur = raw->first;               // curor
    node *ns_cur = no_space_queue->first; // no space curor

    int parentheses = 0;

    char oprs[] = {'*', '/', '^'};
    char oprs1[] = {'+', '-'};
    char operators[] = {'+', '-', '*', '/', '^'};
    int numberCount = 0;

    // ------ first and last number ------
    if (raw->first != nullptr)

        for (char c : oprs) // prohibited: *3-2 || 3-2/

            if (raw->last->val == c || raw->first->val == c)
                return false;

    // ------ numbers in sequence ------
    while (cur != nullptr && cur->next != nullptr) // prohibitions
    {
        char val = cur->val;
        char nextVal = cur->next->val;

        if (isdigit(val) && nextVal == ' ')
        {
            numberCount++;
        }
        if (isOperator(val))
            numberCount = 0;

        if (numberCount > 1)
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
    char operators[] = {'+', '-', '*', '/', '^', '~'};
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
    if (op == '~')
        return 4; // unary operator
    if (op == '^')
        return 3;

    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

void Expression::infix_to_posfix(queue *ifx, queue *pfx)
{
    node *cur = ifx->first;
    stack *oprS = new stack;
    inicialize_stack(oprS);
    while (cur != nullptr)
    {

        if (isdigit(cur->val))
        {
            while (cur != nullptr && isdigit(cur->val))
            {
                enqueue(cur->val, pfx);
                cur = cur->next;
            }
            enqueue(' ', pfx);
            continue;
        }

        if (cur->val == '(')
            push(cur->val, oprS);

        else if (cur->val == ')')
        {
            while (oprS->top != nullptr && oprS->top->val != '(')
                enqueue(pop(oprS), pfx);

            pop(oprS);
        }

        else
        {
            bool isUnary = cur == ifx->first ||
                           (cur->prev && isOperator(cur->prev->val)) ||
                           (cur->prev && cur->prev->val == '(');

            if ((cur->val == '+' || cur->val == '-') && isUnary)
            {
                if (cur->val == '-')
                    push('~', oprS);

                cur = cur->next;
                continue;
            }

            string assoc = (cur->val == '^') ? "right" : "left"; // association

            while (oprS->top != nullptr && oprS->top->val != '(')
            {
                int firstPrec = get_precedence(oprS->top->val);
                int tokPrec = get_precedence(cur->val);

                if ((assoc == "left" && firstPrec >= tokPrec) ||
                    (assoc == "right" && firstPrec > tokPrec))

                    enqueue(pop(oprS), pfx);

                else
                    break;
            }

            push(cur->val, oprS);
        }

        cur = cur->next;
    }
    while (oprS->top != nullptr)
        enqueue(pop(oprS), pfx);

    delete oprS;
}

void Expression::print(queue *ifx, queue *pfx)
{
    node *curIFX = ifx->first;
    node *curPFX = pfx->first;

    cout << "\n";

    while (curIFX != nullptr)
    {
        cout << curIFX->val;

        curIFX = curIFX->next;
    }

    cout << "\n\n";

    while (curPFX != nullptr)
    {
        if ((isOperator(curPFX->val)))
            printf("%c ", curPFX->val);
        else
            cout << curPFX->val;

        curPFX = curPFX->next;
    }

    cout << "\n\n";
}
double Expression::parse_char(node *&cur)
{

    double val = 0;
    double factor = 0.1;

    while (cur != nullptr && isdigit(cur->val))
    {
        val = val * 10 + (cur->val - '0'); // subtract  the ASCII values
        cur = cur->next;
    }

    if (cur != nullptr && (cur->val == '.' || cur->val == ','))
    {
        cur = cur->next;

        while (isdigit(cur->val))
        {
            val += (cur != nullptr && cur->val - '0') * factor;
            factor *= 0.1;
            cur = cur->next;
        }
    }

    return val;
    /*
    val = val * 10 - (ASCII value of char - ASCII value of 0)
    '129'
    val = 0;

    val = 0 * 10 + (49 - 48)
    val = 1

    val = 1 * 10 + (50 - 48)
    val = 10 + 2
    val = 12

    val = 12 * 10 + (57 - 48)
    val = 120 + 9
    val = 129

    */
}

Expression::leaf *Expression::posfix_to_tree(queue *pfx)
{
    tree t;
    inicialize_tree(&t);
    node *cur = pfx->first;

    while (cur != nullptr)
    {
        // cout << "Lendo: [" << cur->val << "]" << endl;

        if (cur->val == ' ')
        {
            cur = cur->next;
            continue;
        }

        if (isdigit(cur->val))
        {
            push_tree(&t, new_leaf_number(parse_char(cur)));
            continue;
        }

        else if (cur->val == '~')
        {
            leaf *right = pop_tree(&t);
            leaf *root = new_leaf(cur->val);
            root->right = right;
            root->left = nullptr;
            push_tree(&t, root);
        }

        else
        {
            leaf *right = pop_tree(&t);
            leaf *left = pop_tree(&t);
            leaf *root = new_leaf(cur->val);
            root->right = right;
            root->left = left;
            push_tree(&t, root);
        }

        cur = cur->next;
    }
    return pop_tree(&t);
}
double Expression::compile(leaf *root)
{
    if (root->isNumber)
        return root->val_number;

    if (root->val == '~')
    {
        double right = compile(root->right);
        return -right;
    }

    double left = compile(root->left);
    double right = compile(root->right);

    switch (root->val)
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