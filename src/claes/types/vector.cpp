#include "claes/iters/vector_items.hpp"
#include "claes/stack.hpp"
#include "claes/types/i64.hpp"
#include "claes/types/iter.hpp"
#include "claes/types/vector.hpp"

namespace claes::types {
  E Vector::call(VM &vm, 
		 Stack &stack, 
		 int arity,
		 const claes::Loc &loc) const {
    vector<Cell> result;

    const auto
      i = stack.items.end() - arity,
      j = stack.items.end();

    move(i, j, back_inserter(result));
    stack.items.erase(i, j);
    stack.push(get(), result);
    return nullopt;
  }

  E Vector::call(Cell &target, 
		 VM &vm, 
		 Stack &stack, 
		 int arity,
		 bool recursive,
		 const claes::Loc &loc) const {
    switch (arity) {
    case 1: {
      const auto i = stack.pop().as(types::I64::get());
      stack.push(target.as(get())[i]);
      break;
    }
    case 2: {
      const auto v = stack.pop();
      const auto i = stack.pop().as(types::I64::get());
      target.as(get())[i] = v;
      stack.push(target);
      break;
    }
    default:
      return Error(loc, "Invalid vector call");
    }

    return nullopt;
  }

  Cell Vector::iter(const Cell &target) const {
    return Cell(Iter::get(), iters::VectorItems::make(target.as(get())));
  }
}
