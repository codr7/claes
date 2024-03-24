#include "claes/env.hpp"
#include "claes/forms.hpp"
#include "claes/forms/ref.hpp"
#include "claes/ops/deref.hpp"
#include "claes/ops/set_ref.hpp"
#include "claes/types/ref.hpp"
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
    } else {
      if (auto e = emit(vm, env, my_args); e) {
	return e;
      }      

      if (auto e = my_args.pop().emit(vm, env, my_args); e) {
	return e;
      }
      
      vm.emit<ops::SetRef>();
    } 
    
    return nullopt;
  }

  Cell Ref::quote(VM &vm, int depth) const {
    return Cell(types::Ref::get(), claes::Ref(target.quote(vm, depth)));
  }
}
