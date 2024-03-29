#include "claes/env.hpp"
#include "claes/forms.hpp"
#include "claes/forms/ref.hpp"
#include "claes/ops/deref.hpp"
#include "claes/ops/make_ref.hpp"
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

  E Ref::quote(VM &vm, Env &env, int depth) const {
    if (const auto e = target.quote(vm, env, depth); e) {
      return e;
    }
    
    vm.emit<ops::MakeRef>();
    return nullopt;
  }
}
