#include "parsing.hpp"
#include "interface.hpp"
#include "operations.hpp"

void CheckAndPushOperation(std::string& infix, std::string& postfix, int& pos, std::stack<std::string>& operation_stack){
  if (pos < infix.size()) {
    switch (infix[pos]) {
      case '(':
        operation_stack.push("(");
        pos++;
        break;

      case ')':
        while (!operation_stack.empty() && operation_stack.top() != "(") {
          postfix += operation_stack.top() + " ";
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
        if (infix[pos] == '-' && (pos < 2 || infix[pos - 1] == '(' ||  infix[pos - 1] == ' ')) {
          tmp = '~';
        }
        if (operation_priority.find(tmp) != operation_priority.end()) {
          if (!operation_stack.empty() && (operation_priority[operation_stack.top()] >= operation_priority[tmp])) {
            postfix += operation_stack.top() + " ";
            operation_stack.pop();
          }
          operation_stack.push(tmp);
          pos++;
        }
    }
  }  
}

std::string ConvertToPostfix(std::string infix) {

  std::stack<std::string> operation_stack;
  std::string postfix = "";
  int pos = 0;
  while(pos < infix.size()) {
    std::string tmp = "";

    while (std::isdigit(infix[pos])) {
      postfix += infix[pos++];
    }
    if (std::isdigit(infix[pos - 1])) {
      postfix += " ";
    }

    while (pos < infix.size() && std::islower(infix[pos])) {
      tmp += infix[pos++];
    }
    if (tmp == "arctg") {
      operation_stack.push(tmp);
      tmp = "";
    }
    if (tmp == "abs") {
      operation_stack.push(tmp);
      tmp = "";
    }
    CheckAndPushOperation(infix, postfix, pos, operation_stack);
  }
  while (!operation_stack.empty()) {
    postfix += operation_stack.top() + " ";
    operation_stack.pop();
  }
  return postfix;
}

std::unique_ptr<ICalculatable> MakeTree(std::istream& expression) {
  std::stack<std::unique_ptr<ICalculatable>> operands_stack;
  int pos = 0;
  std::string tmp;
  while (getline(expression, tmp, ' ')) {
    if (std::isdigit(tmp[0])) {
      operands_stack.push(std::make_unique<Number>(stoi(tmp)));
      continue;
    }
    switch (tmp[0]) {
      case '+': {
        auto right_operand = std::move(operands_stack.top());
        operands_stack.pop();
        auto left_operand = std::move(operands_stack.top());
        operands_stack.pop();
        auto plus = std::make_unique<Plus>(Plus(std::move(left_operand), std::move(right_operand)));
        operands_stack.push(std::move(plus));
        break;
      }

      case '-': {
        auto right_operand = std::move(operands_stack.top());
        operands_stack.pop();
        auto left_operand = std::move(operands_stack.top());
        operands_stack.pop();
        auto minus = std::make_unique<Minus>(Minus(std::move(left_operand), std::move(right_operand)));
        operands_stack.push(std::move(minus));
        break;
      }

      case '~': {
        auto operand = std::move(operands_stack.top());
        operands_stack.pop();
        auto unary_minus = std::make_unique<UnaryMinus>(UnaryMinus(std::move(operand)));
        operands_stack.push(std::move(unary_minus));
        break;
      }

      case '/': {
        auto right_operand = std::move(operands_stack.top());
        operands_stack.pop();
        auto left_operand = std::move(operands_stack.top());
        operands_stack.pop();
        auto divide = std::make_unique<Divide>(Divide(std::move(left_operand), std::move(right_operand)));
        operands_stack.push(std::move(divide));
        break;
      }
      case 'a': {
        if (tmp == "arctg") {
          auto operand = std::move(operands_stack.top());
          operands_stack.pop();
          auto arctg = std::make_unique<Atan>(Atan(std::move(operand)));
          operands_stack.push(std::move(arctg));
          break;
        }
        if (tmp == "abs") {
          auto operand = std::move(operands_stack.top());
          operands_stack.pop();
          auto absolute = std::make_unique<Abs>(Abs(std::move(operand)));
          operands_stack.push(std::move(absolute));
          break;
        }
      }
    }
  }
  
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