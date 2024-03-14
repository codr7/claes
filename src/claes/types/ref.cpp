#include "claes/form.hpp"
#include "claes/ops/set_ref_direct.hpp"
#include "claes/types/ref.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  E Ref::call(const Cell &target, 
	      VM &vm, 
	      Stack &stack, 
	      int arity,
	      const Loc &loc) const {
    return Error(loc, "Calling not implemented for references");
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
