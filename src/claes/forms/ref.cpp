#include "claes/env.hpp"
#include "claes/forms/ref.hpp"
#include "claes/ops/deref.hpp"
#include "claes/vm.hpp"

namespace claes::forms {
  E Ref::emit(VM &vm, Env &env, Forms &args) const {
    return target.emit_ref(vm, env, args, loc);
  }

  E Ref::emit_call(VM &vm, Env &env, const Forms &args, const Loc &loc) const {
    Forms my_args(args);
    
    if (args.empty()) {
      if (auto e = emit(vm, env, my_args); e) {
	return e;
      }
      
      vm.emit<ops::Deref>();
      return nullopt;
    } 
    
    return Error(loc, "Invalid reference update target: &", target);
  }
}
