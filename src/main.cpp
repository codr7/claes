#include <iostream>

#include "claes/libs/core.hpp"
#include "claes/ops/exit.hpp"
#include "claes/stack.hpp"
#include "claes/vm.hpp"

using namespace claes;

int main(int argc, char *argv[]) {
  VM vm;

  if (argc > 1) {
    libs::Core core;
    Env env;
    env.import_from(core);
    Loc loc("main");
    Stack stack;
    
    for (auto i = 1; i < argc; i++) {
      PC start_pc = vm.emit_pc();

      if (auto e = vm.load(argv[i], env, loc); e) {
	cerr << *e << endl;
	return -1;
      }

      vm.emit<ops::Exit>();

      if (auto e = vm.eval(start_pc, stack); e) {
	cerr << *e << endl;
	return -1;
      }
    }
  } else {
    vm.repl(cin, cout);
  }

  return 0;
}
