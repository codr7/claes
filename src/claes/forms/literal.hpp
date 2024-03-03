#ifndef CLAES_FORMS_LITERAL_HPP
#define CLAES_FORMS_LITERAL_HPP

#include "claes/cell.hpp"

namespace claes::forms {
  struct Literal: Form::Imp {
    Cell value;
    
    Literal(const Location &location, const Cell &value): 
      Form::Imp(location), value(value) {}

    virtual optional<Error> emit(VM &vm, Env &env, Forms &arguments) const override {
      return value.emit_literal(vm, env, arguments, location);
    }

    virtual optional<Error> emit_call(VM &vm, 
				      Env &env, 
				      const Forms &arguments, 
				      const Location &location) const override {
      return value.emit_call(vm, env, arguments, location);
    }
  };
}

#endif
