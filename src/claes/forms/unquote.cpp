#include "claes/env.hpp"
#include "claes/forms.hpp"
#include "claes/forms/id.hpp"
#include "claes/forms/literal.hpp"
#include "claes/forms/unquote.hpp"
#include "claes/ops/push.hpp"
#include "claes/types/sym.hpp"
#include "claes/vm.hpp"

namespace claes::forms {
  E Unquote::emit(VM &vm, Env &env, Forms &args) const {
    return Error(loc, "Unquote outside of quoted context");
  }

  E Unquote::quote(VM &vm, Env &env, int depth) const {
    if (--depth) {
      return target.quote(vm, env, depth);
    }
    
    Forms args;
    return target.emit(vm, env, args);
  }
}
