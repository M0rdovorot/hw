#include <iostream>

#include "calculator.hpp"
#include "parsing.hpp"

int main(int argc, char* argv[]){
  if (argc == 1 || (argc == 2 && argv[1] == std::string("--help"))){
    std::cout << "Usage: Type your expression\nExample: (2 + 3 * (5 / 2))\n" << std::endl;
    return 0;
  }
  std::string expression = argv[1];
  try{
    std::cout << ConvertToPostfix(expression) << std::endl;
  }
  catch(const char* error_message){
    std::cout << "ERROR: " << error_message << std::endl;
  }
  return 0;
}