#include "claes/cell.hpp"
#include "claes/ops/push.hpp"
#include "claes/types/macro.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  void Macro::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  E Macro::emit_call(const Cell &value,
		     VM &vm, 
		     Env &env, 
		     const Forms &args,
		     const Loc &loc) const {
    return const_cast<Value &>(value.as(get())).call(vm, env, args, loc);
  }

  E Macro::emit_ref(const Cell &value,
		    VM &vm, 
		    Env &env, 
		    Forms &args,
		    const Loc &loc) const {
    vm.emit<ops::Push>(value);
    return nullopt;
  }
  
  bool Macro::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
