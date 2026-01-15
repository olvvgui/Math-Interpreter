#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <cmath>

#include "Token.h"
#include "Utils.h"
#include "DataStructures.h"

using namespace std;

class Interpreter
{
private:
    void tokens_in_queue(vector<Token> &tokens, queue *ifx);
    void infix_to_posfix(queue *ifx, queue *pfx);
    leaf *posfix_to_tree(queue *pfx);
    double evaluate(leaf *l);

public:
    double run(string expression);
};

#endif