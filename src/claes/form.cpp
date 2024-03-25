#include "claes/form.hpp"
#include "claes/forms.hpp"
#include "claes/ops/call_indirect.hpp"
#include "claes/ops/make_ref.hpp"
#include "claes/vm.hpp"

namespace claes {
  E Form::Imp::emit_call(VM &vm, 
			 Env &env, 
			 const Forms &args, 
			 const Loc &loc) const {
    Forms as(args);
    const auto arity = as.len();

    if (auto e = as.emit(vm, env); e) {
      return e;
    }
	
    if (auto e = emit(vm, env, as); e) {
      return e;
    }
	
    vm.emit<ops::CallIndirect>(arity, loc);
    return nullopt;
  }

  E Form::Imp::emit_ref(VM &vm, Env &env, Forms &args, const Loc &loc) const {
    Forms target_args = args;
    if (auto e = emit(vm, env, args); e) {
      return e;
    }

    vm.emit<ops::MakeRef>();
    return nullopt;
  }

   pair<optional<Cell>, E> Form::quote(VM &vm, int depth) const {
    return imp->quote(vm, depth);
  }
}
