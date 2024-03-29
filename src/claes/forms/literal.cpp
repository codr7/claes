#include "claes/forms/literal.hpp"
#include "claes/ops/push.hpp"
#include "claes/types/sym.hpp"
#include "claes/vm.hpp"

namespace claes::forms {
  E Literal::quote(VM &vm, Env &env, int depth) const {
    vm.emit<ops::Push>(value);
    return nullopt;
  }
}
