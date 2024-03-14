#include "claes/cell.hpp"
#include "claes/form.hpp"
#include "claes/ops/call_direct.hpp"
#include "claes/ops/push.hpp"
#include "claes/types/method.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  E Method::call(Cell &target, 
		 VM &vm, 
		 Stack &stack, 
		 int arity,
		 const Loc &loc) const {
    return target.as(get()).call(vm, stack, arity, loc);
  }

  void Method::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  E Method::emit_call(const Cell &value,
		     VM &vm, 
		     Env &env, 
		     const Forms &args,
		     const Loc &loc) const {
    Forms my_args(args);
    auto arity = 0;

    for (auto a: args.items) {
      if (auto e = a.emit(vm, env, my_args); e) {
	return e;
      }

      arity++;
    }

    vm.emit<ops::CallDirect>(value, arity, loc);
    return nullopt;
  }
  
  E Method::emit_ref(const Cell &value,
		    VM &vm, 
		    Env &env, 
		    Forms &args,
		    const Loc &loc) const {
    vm.emit<ops::Push>(value);
    return nullopt;
  }

  bool Method::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
