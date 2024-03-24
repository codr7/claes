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
    vm.emit<ops::Push>(target.quote(vm, 1));
    return nullopt;
  }

  Cell Quote::quote(VM &vm, int depth) const {
    return target.quote(vm, depth + 1);
  }
}
