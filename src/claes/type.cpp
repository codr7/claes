#include "claes/cell.hpp"
#include "claes/ops/push.hpp"
#include "claes/stack.hpp"
#include "claes/type.hpp"
#include "claes/types/pair.hpp"
#include "claes/vm.hpp"

namespace claes {
  Cell Type::Imp::clone(const Cell &value) const {
    return value;
  }

  Cell Type::clone(const Cell &value) const {
    return imp->clone(value);
  }

  E Type::Imp::call(const Cell &target, 
		    VM &vm, 
		    Stack &stack, 
		    int arity,
		    const Loc &loc) const {
    return Error(loc, "Invalid call target: ", target);
  }

  E Type::Imp::emit_literal(const Cell &value,
			    VM &vm, 
			    Env &env, 
			    Forms &args,
			    const Loc &loc) const {
    vm.emit<ops::Push>(value);
    return nullopt;
  }

  Cell Type::Imp::push(const Cell &target, const Cell &item) const {
    return Cell(types::Pair::get(), make_pair(target, item));
  }

  Cell Type::push(const Cell &target, const Cell &item) const {
    return imp->push(target, item);
  }
}
