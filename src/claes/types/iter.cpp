#include "claes/stack.hpp"
#include "claes/types/iter.hpp"
#include "claes/types/nil.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  E Iter::call(Cell &target, 
	       VM &vm, 
	       Stack &stack, 
	       int arity,
	       const Loc &loc) const {
    const auto [v, e] = target.as(get()).next();
    
    if (e) {
      return e;
    }
    
    if (v) {
      stack.push(*v);
    } else {
      stack.push(types::Nil::get(), nullptr);
    }

    return nullopt;
  }
}
