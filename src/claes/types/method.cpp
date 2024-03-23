#include "claes/cell.hpp"
#include "claes/form.hpp"
#include "claes/ops/call_direct.hpp"
#include "claes/ops/push.hpp"
#include "claes/types/method.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  E Method::call(Cell &target, 
		 VM &vm, 
		 Stack &stack, 
		 int arity,
		 bool recursive,
		 const Loc &loc) const {
    const auto &m = target.as(get());

    if (arity < m.imp->arity) {
      return Error(loc, "Not enough arguments: ", target, ' ', arity);
    }

    return m.call(vm, stack, arity, recursive, loc);
  }

  void Method::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }
  
  E Method::emit_ref(const Cell &value,
		    VM &vm, 
		    Env &env, 
		    Forms &args,
		    const Loc &loc) const {
    vm.emit<ops::Push>(value);
    return nullopt;
  }

  bool Method::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
