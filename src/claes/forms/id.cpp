#include "claes/env.hpp"
#include "claes/forms/id.hpp"

namespace claes::forms {
  optional<Error> Id::emit(VM &vm, Env &env, Forms &arguments) const {
    if (auto found = env.find(name); found) {
      return found->emit_id(vm, env, arguments, location);
    }

    return Error(location, "Unknown identifier: ", name);
  }

  optional<Error> Id::emit_call(VM &vm, 
				Env &env, 
				const Forms &arguments, 
				const Location &location) const {
    const auto target = env.find(name);
    
    if (!target) {
      return Error(location, "Unknown call target: ", name);
    }
    
    return target->emit_call(vm, env, arguments, location);
  }
}
