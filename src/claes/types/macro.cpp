#include "claes/cell.hpp"
#include "claes/types/macro.hpp"

namespace claes::types {
  TType<Macro> Macro::type("Macro");

  void Macro::dump(const Cell &value, ostream &out) const {
    out << value.as(type);
  }

  optional<Error> Macro::emit_call(const Cell &value,
				   VM &vm, 
				   Env &env, 
				   const Forms &arguments,
				   const Location &location) const {
    return value.as(type).call(vm, env, arguments, location);
  }
  
  bool Macro::eq(const Cell &left, const Cell &right) const {
    return left.as(type) == right.as(type);
  }
}
