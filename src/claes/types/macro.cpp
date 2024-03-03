#include "claes/cell.hpp"
#include "claes/types/macro.hpp"

namespace claes::types {
  void Macro::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  E Macro::emit_call(const Cell &value,
		     VM &vm, 
		     Env &env, 
		     const Forms &arguments,
		     const Location &location) const {
    return value.as(get()).call(vm, env, arguments, location);
  }
  
  bool Macro::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
