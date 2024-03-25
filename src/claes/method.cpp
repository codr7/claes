#include <iostream>

#include "claes/method.hpp"
#include "claes/stack.hpp"
#include "claes/types/vector.hpp"

namespace claes {
  E Method::call(VM &vm, Stack &stack, int arity, bool recursive, const Loc &loc) const {
    const auto delta_arity = arity - this->arity() + 1;
      
    if (vararg() && delta_arity > 0) {
      types::Vector::Value vas;

      auto
	i = next(stack.begin(), stack.len() - delta_arity),
	j = stack.end();

      vas.push_back(*i++);
      move(i, j, back_inserter(vas));
      stack.items.erase(i, j);
      arity = this->arity();

      stack.push(types::Vector::get(), vas);
    }
      
    return imp->body(*this, vm, stack, arity, recursive, loc);
  }
}
