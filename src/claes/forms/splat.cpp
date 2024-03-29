#include "claes/env.hpp"
#include "claes/forms.hpp"
#include "claes/forms/splat.hpp"
#include "claes/ops/push.hpp"
#include "claes/ops/splat.hpp"
#include "claes/types/iter.hpp"
#include "claes/types/vector.hpp"
#include "claes/vm.hpp"

namespace claes::forms {
  E Splat::emit(VM &vm, Env &env, Forms &args) const {
    if (auto e = target.emit(vm, env, args); e) {
      return e;
    }

    vm.emit<ops::Splat>();
    return nullopt;
  }

  E Splat::quote(VM &vm, Env &env, int depth) const {
    if (const auto e = target.quote(vm, env, depth); e) {
      return e;
    }

    const auto [t, e] = vm.eval(target, env);

    if (e) {
      return e;
    }

    auto it = t->iter().as(types::Iter::get());
    types::Vector::Value result;
    
    for (;;) {
      auto [v, e] = it.next();

      if (e) {
	return e;
      }

      if (!v) {
	break;
      }

      result.push_back(*v);
    }
  
    vm.emit<ops::Push>(Cell(types::Vector::get(), result));
    return nullopt;
  }
}
