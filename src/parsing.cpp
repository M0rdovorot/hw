#include "parsing.hpp"
#include "interface.hpp"
#include "operations.hpp"

void CheckAndPushOperation(std::string& infix, std::vector<std::string>& postfix, int& pos, std::stack<std::string>& operation_stack){
  if (pos < infix.size()) {
    switch (infix[pos]) {
      case '(':
        operation_stack.push("(");
        pos++;
        break;

      case ')':
        while (!operation_stack.empty() && operation_stack.top() != "(") {
          postfix.push_back(operation_stack.top());
          operation_stack.pop();
        }

        if (operation_stack.empty()) throw "Wrong expression";
        if (operation_stack.top() == "(") operation_stack.pop();
        pos++;
        break;

      case ' ':
        while (infix[pos] == ' ') {
          pos++;
        }
        break;

      default:
        std::string tmp;
        tmp = infix[pos];
        if (infix[pos] == '-' && (pos < 2 || infix[pos - 1] == '(')) {
          tmp = '~';
        }
        if (kOperationPriority.find(tmp) != kOperationPriority.end()) {
          if (!operation_stack.empty() && (kOperationPriority[operation_stack.top()] >= kOperationPriority[tmp])) {
            postfix.push_back(operation_stack.top());
            operation_stack.pop();
          }
          operation_stack.push(tmp);
          pos++;
        }
    }
  }  
}

std::vector<std::string> ConvertToPostfix(std::string infix) {

  std::stack<std::string> operation_stack;
  std::vector<std::string> postfix;
  int pos = 0;
  while(pos < infix.size()) {
    std::string tmp = "";

    while (std::isdigit(infix[pos])) {
      tmp += infix[pos++];
    }
    if (std::isdigit(infix[pos - 1])) {
      postfix.push_back(tmp);
    }

    tmp = "";
    while (pos < infix.size() && std::islower(infix[pos])) {
      tmp += infix[pos++];
    }
    if (tmp == kArctg) {
      operation_stack.push(tmp);
    }
    if (tmp == kAbs) {
      operation_stack.push(tmp);
    }

    CheckAndPushOperation(infix, postfix, pos, operation_stack);
  }
  while (!operation_stack.empty()) {
    postfix.push_back(operation_stack.top());
    operation_stack.pop();
  }
  return postfix;
}

bool IsDigit(std::string str) {
  for (int i = 0; i < str.size(); ++i) {
    if (!std::isdigit(str[i])) return false;
  }
  return true;
}

void PushBinary(std::stack<std::unique_ptr<ICalculatable>>& operands_stack, std::string& operation, std::unique_ptr<ICalculatable> left_operand, std::unique_ptr<ICalculatable> right_operand) {
  switch (operation[0])
  {
    case '/': {
      operands_stack.push(std::move(std::make_unique<Divide>(Divide(std::move(left_operand), std::move(right_operand)))));
      break;
    }

    case '+': {
      operands_stack.push(std::move(std::make_unique<Plus>(Plus(std::move(left_operand), std::move(right_operand)))));
      break;
    }

    case '-': {
      operands_stack.push(std::move(std::make_unique<Minus>(Minus(std::move(left_operand), std::move(right_operand)))));
      break;
    }
  }
}

void PushUnary(std::stack<std::unique_ptr<ICalculatable>>& operands_stack, std::string& operation, std::unique_ptr<ICalculatable> operand) {
  switch (operation[0])
  {
    case '~': {
      operands_stack.push(std::move(std::make_unique<UnaryMinus>(UnaryMinus(std::move(operand)))));
      break;
    }

    case 'a': {
      if (operation == kArctg) {
        operands_stack.push(std::move(std::make_unique<Atan>(Atan(std::move(operand)))));
        break;
      }

      if (operation == kAbs) {
        operands_stack.push(std::move(std::make_unique<Abs>(Abs(std::move(operand)))));
        break;
      }
      throw "wrong expression";
    }

    default: {
      throw "wrong expression";
    }
  }
}

std::unique_ptr<ICalculatable> MakeTree(std::vector<std::string>& expression) {
  std::stack<std::unique_ptr<ICalculatable>> operands_stack;
  int pos = 0;
  std::string tmp;
  for (int i = 0; i < expression.size(); ++i) {
    tmp = expression[i];
    if (IsDigit(tmp)) {
      operands_stack.push(std::make_unique<Number>(stoi(tmp)));
      continue;
    }
    switch (kOperationType[tmp]) {
      case OPERATION_TYPE_BINARY: {
        auto right_operand = std::move(operands_stack.top());
        operands_stack.pop();
        auto left_operand = std::move(operands_stack.top());
        operands_stack.pop();
        PushBinary(operands_stack, tmp, std::move(left_operand), std::move(right_operand));
        break;
      }

      case OPERATION_TYPE_UNARY: {
        auto operand = std::move(operands_stack.top());
        operands_stack.pop();
        PushUnary(operands_stack, tmp, std::move(operand));
        break;
      }
    }
  }
  if (operands_stack.size() > 1) throw operands_stack.size();
  return std::move(operands_stack.top());
}

bool Help(int argc, char* argv[]) {
  if (argc == 1 || (argc == 2 && argv[1] == std::string("--help"))) {
    std::cout << "Usage: Type your expression in single quote. Example: '2 / (-4) + 3 / (5 - 2)'\nAvailiable operations:\n'+' - sum\n'-' - difference\n";
    std::cout << "'/' - divide\n arctg(<expression>) - arc tangent\n abs(<expression>) - absolute value\n(<expression>) - brackets\n";
    std::cout << "(-<expression>) - unary minus\n";
    return true;
  }
  return false;
}