#include "claes/cell.hpp"
#include "claes/form.hpp"
#include "claes/forms.hpp"
#include "claes/ops/call_direct.hpp"
#include "claes/ops/loc.hpp"
#include "claes/ops/make_vector.hpp"
#include "claes/ops/push.hpp"
#include "claes/ops/push_vector_item.hpp"
#include "claes/types/expr.hpp"
#include "claes/types/method.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  E Method::call(Cell &target, 
		 VM &vm, 
		 Stack &stack, 
		 int arity,
		 bool recursive,
		 const claes::Loc &loc) const {
    const auto &m = target.as(get());

    if (arity < m.arity()) {
      return Error(loc, "Not enough arguments: ", target, ' ', arity);
    }

    return m.call(vm, stack, arity, recursive, loc);
  }

  void Method::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  E Method::emit_call(const Cell &value,
		      VM &vm, 
		      Env &env, 
		      const Forms &args,
		      const claes::Loc &loc) const {
    auto &m = value.as(get());

    if (args.len() < m.arity()) {
      return Error(loc, "Not enough arguments for: ", value, ' ', args.len());
    }

    if (vm.debug) {
      vm.emit<ops::Loc>(loc);
    }

    Forms my_args(args);
    auto ma = m.imp->args.rbegin();
    auto arity = 0;
    auto vararg = false;
    
    for (auto a: args.items) {
      if (ma != m.imp->args.rend()) {	
	if (ma->front() == '\'') {
	  vm.emit<ops::Push>(Cell(Expr::get(), claes::Expr(a, env)));
	  ma++;
	  arity++;
	  continue;
	}

	if (ma->back() == '*') {
	  vararg = true;
	  vm.emit<ops::MakeVector>();
	}
	
	ma++;
      }
      
      if (auto e = a.emit(vm, env, my_args); e) {
	return e;
      }

      if (vararg) {
	vm.emit<ops::PushVectorItem>();
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
		     const claes::Loc &loc) const {
    vm.emit<ops::Push>(value);
    return nullopt;
  }

  bool Method::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
