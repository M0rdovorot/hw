#pragma once

#include <string>
#include <map>
#include <memory>
#include <stack>
#include <iostream>
#include <vector>

#include "interface.hpp"

#define OPERATION_L_BRACKET_PRIORITY 0
#define OPERATION_PLUS_PRIORITY 1
#define OPERATION_MINUS_PRIORITY 1
#define OPERATION_DIVIDE_PRIORITY 2
#define OPERATION_ARCTG_PRIORITY 3
#define OPERATION_ABS_PRIORITY 3
#define OPERATION_UNARY_MINUS_PRIORITY 3

inline constexpr std::string_view kLBracket = "(";
inline constexpr std::string_view kRBracket = ")";
inline constexpr std::string_view kPlus = "+";
inline constexpr std::string_view kMinus = "-";
inline constexpr std::string_view kDivide = "/";
inline constexpr std::string_view kArctg = "arctg";
inline constexpr std::string_view kAbs = "abs";
inline constexpr std::string_view kUnaryMinus = "~";

static std::map<std::string_view, int> kOperationPriority = {
  {kLBracket, OPERATION_L_BRACKET_PRIORITY},
  {kPlus, OPERATION_PLUS_PRIORITY}, 
  {kMinus, OPERATION_MINUS_PRIORITY}, 
  {kDivide, OPERATION_DIVIDE_PRIORITY}, 
  {kArctg, OPERATION_ARCTG_PRIORITY},
  {kAbs, OPERATION_ABS_PRIORITY},
  {kUnaryMinus, OPERATION_UNARY_MINUS_PRIORITY}
};

std::vector<std::string> ConvertToPostfix(std::string);
std::unique_ptr<ICalculatable> MakeTree(std::vector<std::string>& expression);
bool Help(int argc, char* argv[]);
void CheckAndPushOperation(std::string& infix, std::vector<std::string>& postfix, int& pos, std::stack<std::string>& operation_stack);