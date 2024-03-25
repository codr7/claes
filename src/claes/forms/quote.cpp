#include "claes/env.hpp"
#include "claes/forms.hpp"
#include "claes/forms/id.hpp"
#include "claes/forms/literal.hpp"
#include "claes/forms/quote.hpp"
#include "claes/ops/push.hpp"
#include "claes/types/sym.hpp"
#include "claes/vm.hpp"

namespace claes::forms {
  E Quote::emit(VM &vm, Env &env, Forms &args) const {
    auto [v, e] = target.quote(vm, 1);

    if (e) {
      return e;
    }

    vm.emit<ops::Push>(*v);
    return nullopt;
  }

  pair<optional<Cell>, E> Quote::quote(VM &vm, int depth) const {
    return target.quote(vm, depth + 1);
  }
}
