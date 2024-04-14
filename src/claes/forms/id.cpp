#include "claes/env.hpp"
#include "claes/forms/id.hpp"
#include "claes/ops/push.hpp"
#include "claes/types/lib.hpp"
#include "claes/types/sym.hpp"
#include "claes/vm.hpp"

namespace claes::forms {
  E Id::emit(VM &vm, Env &env, Forms &arguments) const {
    if (auto [found, e] = find(env); e) {
      return e;
    } else if (found) {
      return found->emit_id(vm, env, arguments, loc);
    }

    return Error(loc, "Unknown identifier: ", name);
  }

  E Id::emit_call(VM &vm, 
		  Env &env, 
		  const Forms &arguments, 
		  const Loc &loc) const {
    const auto [target, e] = find(env);

    if (e) {
      return e;
    }
    
    if (!target) {
      return Error(loc, "Unknown call target: ", name);
    }

    return target->emit_call(vm, env, arguments, loc);
  }

  E Id::emit_ref(VM &vm, Env &env, Forms &arguments, const Loc &loc) const {
    if (auto [found, e] = find(env); e) {
      return e;
    } else if (found) {
      return found->emit_ref(vm, env, arguments, loc);
    }
    
    return Error(loc, "Unknown identifier: ", name);
  }

  pair<optional<Cell>, E> Id::find(Env &env) const {
    auto n = name;
    auto e = &env;

    for (;;) {
      const int i = n.find('/');

      if (i == -1) {
	break;
      }

      const auto prefix = n.substr(0, i);
      const auto v = env.find(prefix);

      if (!v) {
	return make_pair(nullopt, Error(loc, "Unknown identifier: ", prefix));
      }

      n = n.substr(i+1);
      
      
      if (v->type != types::Lib::get()) {
	return make_pair(nullopt, Error(loc, "Expected lib: ", v->type));
      }
      
      e = v->as(types::Lib::get());
    }
    
    if (auto found = e->find(n); found) {
      return make_pair(*found, nullopt);
    }

    return make_pair(nullopt, Error(loc, "Unknown identifier: ", n));
  }
  
  E Id::quote(VM &vm, Env &env, int depth) const {
    vm.emit<ops::Push>(Cell(types::Sym::get(), vm.sym(name)));
    return nullopt; 
  }
}
