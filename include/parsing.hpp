#pragma once

#include <string>
#include <map>
#include <memory>
#include <stack>
#include <iostream>

#include "calculator.hpp"

#define OPERATION_L_BRACKET_PRIORITY 0
#define OPERATION_PLUS_PRIORITY 1
#define OPERATION_MINUS_PRIORITY 1
#define OPERATION_DIVIDE_PRIORITY 2
#define OPERATION_ARCTG_PRIORITY 3

std::string ConvertToPostfix(std::string);
std::unique_ptr<ICalculatable> MakeTree(std::istream& expression);