#include "claes/forms/pair.hpp"
#include "claes/types/pair.hpp"
#include "claes/ops/make_pair.hpp"
#include "claes/vm.hpp"

namespace claes::forms {
  E Pair::emit(VM &vm, Env &env, Forms &args) const {
    if (auto e = left.emit(vm, env, args); e) {
      return e;
    }

    if (auto e = right.emit(vm, env, args); e) {
      return e;
    }

    vm.emit<ops::MakePair>();
    return nullopt;
  }

  Cell Pair::quote(VM &vm, int depth) const {
    return Cell(types::Pair::get(),
		make_pair(left.quote(vm, depth), right.quote(vm, depth)));
  }
}
