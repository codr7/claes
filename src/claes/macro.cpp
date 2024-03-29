#include "claes/form.hpp"
#include "claes/forms.hpp"
#include "claes/macro.hpp"
#include "claes/ops/loc.hpp"
#include "claes/vm.hpp"

namespace claes {
  E Macro::call(VM &vm, 
		Env &env, 
		const Forms &args,
		const Loc &loc) {
    if (args.len() < imp->arity) {
      return Error(loc, 
		   "Not enough arguments for: ", *this, ' ', 
		   imp->arity, ':', args.len());
    }

    if (vm.debug) {
      vm.emit<ops::Loc>(loc);
    }
    
    return imp->body(*this, vm, env, args, loc);
  }
}
