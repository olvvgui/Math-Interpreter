#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <limits>
using namespace std;

bool isOperator(char op);
char returnOperator(char op);
int get_precedence(char op);
void enter_to_continue();

#endif