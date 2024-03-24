#include "claes/cell.hpp"
#include "claes/form.hpp"
#include "claes/forms.hpp"
#include "claes/ops/call_reg.hpp"
#include "claes/ops/get_reg.hpp"
#include "claes/types/reg.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  void Reg::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  E Reg::emit_call(const Cell &value,
		   VM &vm, 
		   Env &env, 
		   const Forms &args,
		   const Loc &loc) const {
    Forms my_args(args);
    const auto arity = my_args.len();

    if (auto e = my_args.emit(vm, env); e) {
      return e;
    }

    vm.emit<ops::CallReg>(value.as(get()), arity, loc);
    return nullopt;
  }

  E Reg::emit_id(const Cell &value,
		 VM &vm, 
		 Env &env, 
		 Forms &args,
		 const Loc &loc) const {
    vm.emit<ops::GetReg>(value.as(get()));
    return nullopt;
  }

  bool Reg::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
