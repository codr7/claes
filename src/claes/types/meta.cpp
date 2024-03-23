#include "claes/cell.hpp"
#include "claes/ops/push.hpp"
#include "claes/types/meta.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  E Meta::call(Cell &target, 
	       VM &vm, 
	       Stack &stack, 
	       int arity,
	       bool recursive,
	       const claes::Loc &loc) const {
    return target.as(get()).call(vm, stack, arity, loc);
  }

  void Meta::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  E Meta::emit_ref(const Cell &value,
		   VM &vm, 
		   Env &env, 
		   Forms &args,
		   const claes::Loc &loc) const {
    vm.emit<ops::Push>(value);
    return nullopt;
  }

  bool Meta::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
