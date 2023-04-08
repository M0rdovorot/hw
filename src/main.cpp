#include <iostream>
#include <sstream>

#include "interface.hpp"
#include "operations.hpp"
#include "parsing.hpp"

int main(int argc, char* argv[]) {
  if (Help(argc, argv)) {
    return 0;
  }
  std::string expression = argv[1];
  try {
    std::vector<std::string> postfix_expression(ConvertToPostfix(expression));
    auto root = MakeTree(postfix_expression);
    std::cout << root->Calculate() << std::endl;
  }
  catch(const char* error_message) {
    std::cout << error_message << std::endl;
  }
  catch(unsigned long error) {
    std::cout << error << std::endl;
  }
  return 0;
}