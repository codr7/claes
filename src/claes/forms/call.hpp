#ifndef CLAES_FORMS_CALL_HPP
#define CLAES_FORMS_CALL_HPP

#include "claes/form.hpp"

namespace claes::forms {
  struct Call: Form::Imp {
    static Form make(const Loc &loc, 
		     const Form &target, 
		     const Forms args) {
      return Form::make<Call>(loc, target, args);
    };

    Form target;
    Forms args;

    Call(const Loc &loc, const Form &target, const Forms args): 
      Form::Imp(loc), target(target), args(args) {}

    virtual E emit(VM &vm, Env &env, Forms &args) const {
      return target.emit_call(vm, env, this->args, loc);
    }
  };
}

#endif
