#include "claes/stack.hpp"
#include "claes/types/sym.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  E Sym::call(VM &vm, 
	      Stack &stack, 
	      int arity,
	      const claes::Loc &loc) const {
    const auto i = next(stack.begin(), stack.len() - arity), j = stack.end();
    reverse(i, j);
    stringstream buffer;

    if (!arity) {
      return Error(loc, "Not enough arguments");
    }
      
    while (--arity) {
      stack.pop().say(buffer);
    }

    auto &v = stack.peek();
    v.say(buffer);
    v = Cell(types::Sym::get(), vm.sym(buffer.str()));
    return nullopt;
  }
}
