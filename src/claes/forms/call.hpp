#ifndef CLAES_FORMS_CALL_HPP
#define CLAES_FORMS_CALL_HPP

#include "claes/form.hpp"

namespace claes::forms {
  struct Call: Form::Imp {
    static Form make(const Loc &loc, 
		     const Form &target, 
		     const Forms arguments) {
      return Form::make<Call>(loc, target, arguments);
    };

    Form target;
    Forms arguments;

    Call(const Loc &loc, const Form &target, const Forms arguments): 
      Form::Imp(loc), target(target), arguments(arguments) {}

    virtual E emit(VM &vm, Env &env, Forms &arguments) const {
      return target.emit_call(vm, env, this->arguments, loc);
    }
  };
}

#endif
