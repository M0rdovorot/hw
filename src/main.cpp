#include <iostream>
#include <sstream>

#include "interface.hpp"
#include "operations.hpp"
#include "parsing.hpp"

int main(int argc, char* argv[]){
  if (argc == 1 || (argc == 2 && argv[1] == std::string("--help"))){
    std::cout << "Usage: Type your expression in single quote. Example: '2 / (-4) + 3 / (5 - 2)'\nAvailiable operations:\n'+' - sum\n'-' - difference\n";
    std::cout << "'/' - divide\n arctg(<expression>) - arc tangent\n abs(<expression>) - absolute value\n(<expression>) - brackets\n";
    std::cout << "(-<expression>) - unary minus\n";
    return 0;
  }
  std::string expression = argv[1];
  try{
    std::istringstream postfix_expression("  " + ConvertToPostfix(expression));
    auto root = MakeTree(postfix_expression);
    std::cout << root->Calculate() << std::endl;
  }
  catch(const char* error_message){
    std::cout << "ERROR: " << error_message << std::endl;
  }
  return 0;
}