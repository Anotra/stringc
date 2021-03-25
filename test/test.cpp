
#include <iostream>
#include <string>
#include <stringc/string.h>

int main() {
  std::string hello;
  std::cin >> hello;
  std::cout << utf8len(hello.c_str(), NULL) << std::endl;
}