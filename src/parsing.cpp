#include "parsing.hpp"
#include "calculator.hpp"

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

    if (pos < infix.size()){
      switch (infix[pos]){
        case '(':
          operation_stack.push("(");
          pos++;
          break;

        case ')':
          while (!operation_stack.empty() && operation_stack.top() != "("){
            postfix += operation_stack.top() + " ";
            operation_stack.pop();
          }

          if (operation_stack.empty()) throw "Wrong expression";
          if (operation_stack.top() == "(") operation_stack.pop();
          pos++;
          break;

        case ' ':
          while (infix[pos] == ' '){
            pos++;
          }
          break;

        default:
          tmp = infix[pos];
          if (operation_priority.find(tmp) != operation_priority.end()){
            if (!operation_stack.empty() && (operation_priority[operation_stack.top()] >= operation_priority[tmp])){//?
              postfix += operation_stack.top() + " ";
              operation_stack.pop();
            }
            operation_stack.push(tmp);
            pos++;
          }
      }
    }
  }
  while (!operation_stack.empty()){
    postfix += operation_stack.top() + " ";
    operation_stack.pop();
  }
  return postfix;
}

std::unique_ptr<ICalculatable> MakeTree(std::istream& expression){
  std::stack<ICalculatable> operands_stack;
  int pos = 0;
  std::string tmp;

  while (getline(expression, tmp, ' '))
  {
    if (std::isdigit(tmp[0])){
      operands_stack.push(static_cast<ICalculatable>(stoi(tmp)));
      continue;
    }
    switch (tmp[0])
    {
      case '+':
      {
        auto right_operand = std::make_unique<ICalculatable>(operands_stack.top());
        auto left_operand = std::make_unique<ICalculatable>(operands_stack.top());
        Plus plus(std::move(left_operand), std::move(right_operand));
        operands_stack.push(plus);
        break;
      }

      case '-':
      {
        auto right_operand = std::make_unique<ICalculatable>(operands_stack.top());
        auto left_operand = std::make_unique<ICalculatable>(operands_stack.top());
        Minus minus(std::move(left_operand), std::move(right_operand));
        operands_stack.push(minus);
        break;
      }

      case '/':
      {
        auto right_operand = std::make_unique<ICalculatable>(operands_stack.top());
        auto left_operand = std::make_unique<ICalculatable>(operands_stack.top());
        Divide divide(std::move(left_operand), std::move(right_operand));
        operands_stack.push(divide);
        break;
      }
      case 'a':
      {
        if (tmp == "arctg"){
          auto operand = std::make_unique<ICalculatable>(operands_stack.top());
          Atan arctg(std::move(operand));
          operands_stack.push(arctg);
          break;
        }
        if (tmp == "abs"){
          auto operand = std::make_unique<ICalculatable>(operands_stack.top());
          Abs absolute(std::move(operand));
          operands_stack.push(absolute);
          break;
        }
      }
    }
  }
  
  auto root = std::make_unique<ICalculatable>(operands_stack.top());
  return std::move(root);
}