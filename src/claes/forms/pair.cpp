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

  pair<optional<Cell>, E> Pair::quote(VM &vm, int depth) const {
    auto [lv, le] = left.quote(vm, depth);

    if (le) {
      return make_pair(nullopt, le);
    }

    auto [rv, re] = right.quote(vm, depth);

    if (re) {
      return make_pair(nullopt, re);
    }

    auto result = Cell(types::Pair::get(), make_pair(*lv, *rv));
    return make_pair(result, nullopt);
  }
}
