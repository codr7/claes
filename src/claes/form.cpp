#include "claes/form.hpp"
#include "claes/ops/call_indirect.hpp"
#include "claes/vm.hpp"

namespace claes {
  E Form::Imp::emit_call(VM &vm, 
			 Env &env, 
			 const Forms &arguments, 
			 const Location &location) const {
    Forms as(arguments);

    if (auto e = as.emit(vm, env); e) {
      return e;
    }
	
    if (auto e = emit(vm, env, as); e) {
      return e;
    }
	
    vm.emit<ops::CallIndirect>(location);
    return nullopt;
  }
}
