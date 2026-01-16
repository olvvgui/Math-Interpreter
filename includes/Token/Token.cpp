#include "Token.h"

Token NumberToken(double val)
{
    Token t;
    t.type = NUMBER;
    t.val = val;
    return t;
}

Token OperatorToken(char op)
{
    Token t;
    if (op == '+' || op == '-')
        t.type = UNARY_OPERATOR;

    else
        t.type = BINARY_OPERATOR;
    t.op = op;
    return t;
}

vector<Token> tokenize(string &expr)
{
    vector<Token> tokens;
    size_t i = 0;
    bool expectingUnary = true;
    while (i < expr.size())
    {

        if (expr[i] == ' ')
        {
            i++;
            continue;
        }

        if (isdigit(expr[i]))
        {

            double val = 0;
            double factor = 0.1;

            while (i < expr.size() && isdigit(expr[i]))
            {
                val = val * 10 + (expr[i] - '0'); // subtract  the ASCII values
                i++;
            }

            if (i < expr.size() && (expr[i] == '.' || expr[i] == ','))
            {

                i++;
                while (i < expr.size() && isdigit(expr[i]))
                {
                    val += (expr[i] - '0') * factor;
                    factor *= 0.1;
                    i++;
                }
            }
            tokens.push_back({NUMBER, val, 0});
            expectingUnary = false;
            continue;
        }
        if (isOperator(expr[i]))
        {
            if (expr[i] == '*' || expr[i] == '/' || expr[i] == '^')
                tokens.push_back({BINARY_OPERATOR, 0, expr[i]});

            else
            {
                if (expectingUnary == true)
                    tokens.push_back({UNARY_OPERATOR, 0, expr[i]});
                else
                    tokens.push_back({BINARY_OPERATOR, 0, expr[i]});
            }
            i++;
            expectingUnary = true;
            continue;
        }
        if (expr[i] == '(')
        {
            tokens.push_back({LPAREN, 0, '('});
            i++;
            expectingUnary = true;
            continue;
        }
        if (expr[i] == ')')
        {
            tokens.push_back({RPAREN, 0, ')'});
            i++;
            expectingUnary = false;
            continue;
        }
        i++;
    }
    return tokens;
}

void print_tokens(vector<Token> &tokens)
{
    cout << endl;
    for (Token &t : tokens)
    {
        if (t.type == NUMBER)
            cout << "[" << t.val << "] ";
        else
            cout << "[" << t.op << "] ";
    }
    cout << "\n";
}
