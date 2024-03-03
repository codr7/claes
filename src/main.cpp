#include <iostream>

#include "claes/vm.hpp"

using namespace claes;

int main() {
  VM vm;
  vm.repl(cin, cout);
  return 0;
}
