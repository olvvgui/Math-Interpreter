#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <limits>
using namespace std;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BOLD = "\033[1m";
const string RESET = "\033[0m";

bool isOperator(char op);
char returnOperator(char op);
int get_precedence(char op);

void enter_to_continue();
void hide_cursor();
void show_cursor();
void show_screen();
#endif