#include "claes/cell.hpp"
#include "claes/types/curl.hpp"
#include "claes/types/string.hpp"
#include "claes/stack.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  E Curl::call(VM &vm, 
	       Stack &stack, 
	       int arity,
	       const claes::Loc &loc) const {
    stack.push(types::Curl::get(), claes::Curl());
    return nullopt;
  }

  E Curl::call(Cell &target, 
	       VM &vm, 
	       Stack &stack, 
	       int arity,
	       bool recursive,
	       const claes::Loc &loc) const {
    return target.as(get()).call(vm, stack, arity, loc);
  };
  
  void Curl::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  bool Curl::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
