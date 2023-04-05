#pragma once

#include <string>
#include <map>
#include <memory>
#include <stack>
#include <iostream>

#include "interface.hpp"

#define OPERATION_L_BRACKET_PRIORITY 0
#define OPERATION_PLUS_PRIORITY 1
#define OPERATION_MINUS_PRIORITY 1
#define OPERATION_DIVIDE_PRIORITY 2
#define OPERATION_ARCTG_PRIORITY 3
#define OPERATION_ABS_PRIORITY 3
#define OPERATION_UNARY_MINUS_PRIORITY 3

static std::map<std::string, int> operation_priority = {
  {"(", OPERATION_L_BRACKET_PRIORITY},
  {"+", OPERATION_PLUS_PRIORITY}, 
  {"-", OPERATION_MINUS_PRIORITY}, 
  {"/", OPERATION_DIVIDE_PRIORITY}, 
  {"arctg", OPERATION_ARCTG_PRIORITY},
  {"abs", OPERATION_ABS_PRIORITY},
  {"~", OPERATION_UNARY_MINUS_PRIORITY}
};

std::string ConvertToPostfix(std::string);
std::unique_ptr<ICalculatable> MakeTree(std::istream& expression);
bool Help(int argc, char* argv[]);
void CheckAndPushOperation(std::string& infix, std::string& postfix, int& pos, std::stack<std::string>& operation_stack);