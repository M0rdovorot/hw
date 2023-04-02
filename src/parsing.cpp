#include "parsing.hpp"


std::string ConvertToPostfix(std::string infix){
  std::map<std::string, int> operation_priority = {
    {"(", OPERATION_L_BRACKET_PRIORITY},
    {"+", OPERATION_PLUS_PRIORITY}, 
    {"-", OPERATION_MINUS_PRIORITY}, 
    {"/", OPERATION_DIVIDE_PRIORITY}, 
    {"arctg", OPERATION_ARCTG_PRIORITY}
  };
  std::stack<std::string> operation_stack;
  std::string postfix = "";
  int pos = 0;
  while(pos < infix.size()){
    std::string tmp = "";

    while (std::isdigit(infix[pos])){
      postfix += infix[pos++];
    }
    if (std::isdigit(infix[pos - 1])){
      postfix += " ";
    }

    while (pos < infix.size() && std::islower(infix[pos])){
      tmp += infix[pos++];
    }
    if (tmp == "arctg"){
      operation_stack.push(tmp);
      tmp = "";
    }

    if (pos < infix.size() && infix[pos] == '('){
      operation_stack.push("(");
      pos++;
    }

    if (pos < infix.size() && infix[pos] == ')'){
      while (!operation_stack.empty() && operation_stack.top() != "("){
        postfix += operation_stack.top() + " ";
        operation_stack.pop();
      }

      if (operation_stack.empty()) throw "Wrong expression";
      if (operation_stack.top() == "(") operation_stack.pop();
      pos++; 
    }

    if (pos < infix.size() && infix[pos] != '(') tmp = infix[pos];
    if (operation_priority.find(tmp) != operation_priority.end()){
      if (!operation_stack.empty() && (operation_priority[operation_stack.top()] >= operation_priority[tmp])){//?
        postfix += operation_stack.top() + " ";
        operation_stack.pop();
      }
      operation_stack.push(tmp);
      pos++;
    }

    while (pos < infix.size() && infix[pos] == ' '){
      pos++;
    }
  }
  while (!operation_stack.empty()){
    postfix += operation_stack.top() + " ";
    operation_stack.pop();
  }
  return postfix;
}