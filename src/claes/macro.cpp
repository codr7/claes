#include "claes/macro.hpp"
#include "claes/ops/loc.hpp"
#include "claes/vm.hpp"

namespace claes {
  E Macro::call(VM &vm, 
		Env &env, 
		const Forms &args,
		const Loc &loc) {
    if (vm.debug) {
      vm.emit<ops::Loc>(loc);
    }
    
    return imp->body(*this, vm, env, args, loc);
  }
}
