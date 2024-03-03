#ifndef CLAES_FORMS_CALL_HPP
#define CLAES_FORMS_CALL_HPP

#include "claes/form.hpp"

namespace claes::forms {
  struct Call: Form::Imp {
    static Form make(const Location &location, 
		     const Form &target, 
		     const Forms arguments) {
      return Form::make<Call>(location, target, arguments);
    };

    Form target;
    Forms arguments;

    Call(const Location &location, const Form &target, const Forms arguments): 
      Form::Imp(location), target(target), arguments(arguments) {}

    virtual optional<Error> emit(VM &vm, Env &env, Forms &arguments) const {
      return target.emit_call(vm, env, this->arguments, location);
    }
  };
}

#endif
