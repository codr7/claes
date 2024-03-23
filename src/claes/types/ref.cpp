#include "claes/form.hpp"
#include "claes/ops/set_ref_direct.hpp"
#include "claes/stack.hpp"
#include "claes/types/ref.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  E Ref::call(Cell &target, 
	      VM &vm, 
	      Stack &stack, 
	      int arity,
	      bool recursive,
	      const Loc &loc) const {
    if (arity == 0) {
      stack.push(target.as(get()).imp->value);
    } else {
      auto &s = stack.peek();
      target.as(get()).imp->value = s;
      s = target;
    }

    return nullopt;
  }

  E Ref::emit_call(const Cell &value,
		   VM &vm, 
		   Env &env, 
		   const Forms &args,
		   const Loc &loc) const {
    Forms my_args(args);

    if (auto e = my_args.pop().emit(vm, env, my_args); e) {
      return e;
    }
    
    vm.emit<ops::SetRefDirect>(value.as(get()));
    return nullopt;
  }
}
