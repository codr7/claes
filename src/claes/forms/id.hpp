#ifndef CLAES_FORMS_ID_HPP
#define CLAES_FORMS_ID_HPP

#include "claes/form.hpp"

namespace claes::forms {
  struct Id: Form::Imp {
    static Form make(const Location &location, const string &name) {
      return Form::make<Id>(location, name);
    };

    string name;
    Id(const Location &location, const string &name): 
      Form::Imp(location), name(name) {}
    
    virtual E emit(VM &vm, Env &env, Forms &arguments) const override;

    virtual E emit_call(VM &vm, 
			Env &env, 
			const Forms &arguments, 
			const Location &location) const override;
  };
}

#endif
