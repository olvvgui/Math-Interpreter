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
                while (isdigit(expr[i]))
                {
                    val += (expr[i] - '0') * factor;
                    factor *= 0.1;
                    i++;
                }
            }
            tokens.push_back({NUMBER, val, 0});
            continue;
        }
        if (isOperator(expr[i]))
        {
            tokens.push_back({OPERATOR, 0, expr[i]});
            i++;
            continue;
        }
        if (expr[i] == '(')
        {
            tokens.push_back({LPAREN, 0, 0});
            i++;
            continue;
        }
        if (expr[i] == ')')
        {
            tokens.push_back({RPAREN, 0, 0});
            i++;
            continue;
        }
        i++;
        // printerro
    }
    return tokens;
}

bool verify_expression(vector<Token> &tokens)
{

    Token *nextTok = nullptr;
    Token *prevTok = nullptr;
    int parentheses = 0;
    string parenthesis_error = "ERROR!!! Parenthesis Misuse";

    if (tokens[0].type != NUMBER &&
        tokens[0].type != UNARY_OPERATOR &&
        tokens[0].type != LPAREN)
        return false;

    if (tokens.back().type != NUMBER &&
        tokens.back().type != RPAREN)
    {
        cout << "cu0" << endl;
        return false;
    }

    for (size_t i = 0; i < tokens.size(); i++)
    {
        prevTok = (i > 0) ? &tokens[i - 1] : nullptr;

        nextTok = (i + 1 < tokens.size()) ? &tokens[i + 1] : nullptr;

        Token &t = tokens[i];

        if (nextTok != nullptr)
        {
            if (t.type == NUMBER && nextTok->type == NUMBER)
            {
                cout << "ERROR!!! Consecutive Numbers" << endl;
                return false; // consecutive numbers
            }
            if (t.type == BINARY_OPERATOR && nextTok->type == BINARY_OPERATOR)
            {
                cout << "ERROR!!! Consecutive Operators" << endl;
                return false; // consecutive operators
            }
            if (t.type == UNARY_OPERATOR && nextTok->type == BINARY_OPERATOR)
            {
                cout << "ERROR!!! Consecutive Operators" << endl;
                return false; // consecutive operators
            }

            if (t.type == LPAREN)
            {
                if (nextTok->type != UNARY_OPERATOR &&
                    nextTok->type != NUMBER &&
                    nextTok->type != LPAREN)
                {
                    cout << parenthesis_error << endl;
                    return false; // (*
                }
            }
            if (t.type == RPAREN)
            {
                if (prevTok != nullptr &&
                    (prevTok->type != NUMBER &&
                     prevTok->type != RPAREN))
                {
                    cout << parenthesis_error << endl;
                    return false; // *)
                }

                if (nextTok->type == NUMBER)
                {
                    cout << parenthesis_error << endl;
                    return false;
                }
            }
        }
        if (t.type == LPAREN)
            parentheses++;

        if (t.type == RPAREN)
        {
            parentheses--;
            if (parentheses < 0)
            {
                cout << parenthesis_error << endl;
                return false; // p: unqual parenthesis
            }
        }
    }
    if (parentheses != 0)
    {
        cout << parenthesis_error << endl;
        return false;
    }
    return true;
}

void print_tokens(vector<Token> &tokens)
{

    for (Token &t : tokens)
    {
        if (t.type == NUMBER)
            cout << "[" << t.val << "] ";
        else
            cout << "[" << t.op << "] ";
    }
    cout << "\n";
}
