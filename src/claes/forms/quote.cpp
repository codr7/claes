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
    return target.quote(vm, env, 1);
  }

  E Quote::quote(VM &vm, Env &env, int depth) const {
    return target.quote(vm, env, depth + 1);
  }
}
