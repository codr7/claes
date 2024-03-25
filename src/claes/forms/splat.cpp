#include "claes/env.hpp"
#include "claes/forms.hpp"
#include "claes/forms/splat.hpp"
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

  pair<optional<Cell>, E> Splat::quote(VM &vm, int depth) const {
    const auto [t, e] = target.quote(vm, depth);

    if (e) {
      return make_pair(nullopt, e);
    }
    
    auto it = t->iter().as(types::Iter::get());
    types::Vector::Value result;
    
    for (;;) {
      auto [v, e] = it.next();

      if (e) {
	return make_pair(nullopt, e);
      }

      if (!v) {
	break;
      }

      result.push_back(*v);
    }
    
    return make_pair(Cell(types::Vector::get(), result),
		     nullopt);
  }
}
