#include "Interpreter.h"

void Interpreter::tokens_in_queue(vector<Token> &tokens, queue *ifx)
{
    for (Token &t : tokens)
    {
        enqueue(ifx, t);
    }
}

bool Interpreter::parse(queue *ifx, queue *pfx)
{
    node *cur = ifx->first;

    stack *oprS = new stack;
    inicialize_stack(oprS);

    bool expectingOperand = true;

    while (cur != nullptr)
    {
        Token &tok = cur->tok;

        if (expectingOperand &&
            tok.type != NUMBER &&
            tok.type != UNARY_OPERATOR &&
            tok.type != LPAREN)

        {
            print_error(SyntaxError);
            return false;
        }
        else if (!expectingOperand &&
                 tok.type != BINARY_OPERATOR &&
                 tok.type != RPAREN)
        {
            print_error(SyntaxError);
            return false;
        }

        if (tok.type == NUMBER)
        {
            enqueue(pfx, tok);
            expectingOperand = false;
        }

        else if (tok.type == LPAREN)
        {
            push(tok.op, oprS);
            expectingOperand = true;
        }

        else if (tok.type == RPAREN)
        {
            while (oprS->top != nullptr && oprS->top->val != '(')
            {
                enqueue(pfx, OperatorToken(pop(oprS)));
            }
            if (oprS->top == nullptr)
            {
                print_error(UnmatchedParenthesis);
                return false;
            }

            pop(oprS);
            expectingOperand = false;
        }

        else
        {

            char op = tok.op;
            if (tok.type == UNARY_OPERATOR && tok.op == '-')
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
            expectingOperand = true;
        }

        cur = cur->next;
    }
    while (oprS->top != nullptr)
    {
        if (oprS->top->val == '(')
        {
            print_error(UnmatchedParenthesis);
            return false;
        }
        enqueue(pfx, OperatorToken(pop(oprS)));
    }

    delete oprS;
    return true;
}

leaf *Interpreter::posfix_to_tree(queue *pfx)
{
    tree t;
    inicialize_tree(&t);
    node *cur = pfx->first;

    while (cur != nullptr)
    {

        Token &tok = cur->tok;

        if (tok.type == NUMBER)
        {
            push_tree(&t, new_leaf(tok));
            cur = cur->next;
            continue;
        }

        else if (tok.op == '~')
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

double Interpreter::evaluate(leaf *root)
{
    Token &tok = root->tok;
    if (tok.type == NUMBER)
        return tok.val;

    if (tok.op == '~')
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

void Interpreter::run(string expression)
{
    const string GREEN = "\033[32m";
    const string BOLD = "\033[1m";
    const string RESET = "\033[0m";

    queue q;
    queue posfix;
    tree t;
    vector<Token> tokens;
    inicialize_queue(&q);
    inicialize_queue(&posfix);
    inicialize_tree(&t);

    tokens = tokenize(expression);
    // print_tokens(tokens);

    tokens_in_queue(tokens, &q);

    bool isValid = parse(&q, &posfix);

    if (!isValid)
        return;

    leaf *l = posfix_to_tree(&posfix);

    double result = evaluate(l);

    cout << BOLD << "\nResult: " << RESET;

    cout << GREEN << result << RESET << endl;

    return;
}