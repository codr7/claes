#include "claes/cell.hpp"
#include "claes/form.hpp"
#include "claes/iters/repeat.hpp"
#include "claes/ops/call_direct.hpp"
#include "claes/ops/push.hpp"
#include "claes/type.hpp"
#include "claes/types/iter.hpp"
#include "claes/types/pair.hpp"
#include "claes/types/ref.hpp"
#include "claes/vm.hpp"

namespace claes {
  Cell Type::Imp::clone(const Cell &value) const {
    return value;
  }

  Cell Type::clone(const Cell &value) const {
    return imp->clone(value);
  }

  E Type::Imp::call(VM &vm, 
		    Stack &stack, 
		    int arity,
		    const Loc &loc) const {
    return Error(loc, "Invalid call target");
  }

  
  E Type::Imp::call(Cell &target, 
		    VM &vm, 
		    Stack &stack, 
		    int arity,
		    const Loc &loc) const {
    return Error(loc, "Invalid call target: ", target);
  }

  E Type::Imp::emit_call(const Cell &value,
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

  E Type::Imp::emit_literal(const Cell &value,
			    VM &vm, 
			    Env &env, 
			    Forms &args,
			    const Loc &loc) const {
    vm.emit<ops::Push>(value);
    return nullopt;
  }

  E Type::Imp::emit_ref(const Cell &value,
			VM &vm, 
			Env &env, 
			Forms &args,
			const Loc &loc) const {
    vm.emit<ops::Push>(Cell(types::Ref::get(), Ref(value)));
    return nullopt;
  }


  Cell Type::Imp::iter(const Cell &target) const {
    return Cell(types::Iter::get(), iters::Repeat::make(target, 1)); 
  }

  void Type::Imp::push(Cell &target, const Cell &item) const {
    target = Cell(types::Pair::get(), make_pair(item, target));
  }

  Cell Type::iter(const Cell &target) const {
    return imp->iter(target);
  }

  void Type::push(Cell &target, const Cell &item) const {
    imp->push(target, item);
  }
}
