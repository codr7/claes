#include "claes/forms/pair.hpp"
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
}
