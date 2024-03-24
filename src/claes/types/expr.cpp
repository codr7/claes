#include "claes/form.hpp"
#include "claes/forms.hpp"
#include "claes/stack.hpp"
#include "claes/types/expr.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  E Expr::call(Cell &target, 
	      VM &vm, 
	      Stack &stack, 
	      int arity,
	      bool recursive,
	      const claes::Loc &loc) const {
    auto &x = target.as(get());

    if (x.pc) {
      const auto prev_pc = vm.pc;
      
      if (auto e = vm.eval(*x.pc, stack); e) {
	return e;
      }
      
      vm.pc = prev_pc;
    }
    
    x.pc = vm.emit_pc() + 1;
    const auto prev_pc = vm.pc;
    
    if (auto e = vm.eval(x.form, x.env, stack); e) {
      return e;
    }
    
    vm.pc = prev_pc;
    return nullopt;
  }
}
