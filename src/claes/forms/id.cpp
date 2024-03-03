#include "claes/env.hpp"
#include "claes/forms/id.hpp"

namespace claes::forms {
  E Id::emit(VM &vm, Env &env, Forms &arguments) const {
    if (auto found = env.find(name); found) {
      return found->emit_id(vm, env, arguments, loc);
    }

    return Error(loc, "Unknown identifier: ", name);
  }

  E Id::emit_call(VM &vm, 
		  Env &env, 
		  const Forms &arguments, 
		  const Loc &loc) const {
    const auto target = env.find(name);
    
    if (!target) {
      return Error(loc, "Unknown call target: ", name);
    }
    
    return target->emit_call(vm, env, arguments, loc);
  }
}
