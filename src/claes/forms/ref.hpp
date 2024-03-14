#ifndef CLAES_FORMS_REF_HPP
#define CLAES_FORMS_REF_HPP

#include "claes/form.hpp"

namespace claes::forms {
  struct Ref: Form::Imp {
    static Form make(const Loc &loc, const Form &target) {
      return Form::make<Ref>(loc, target);
    };

    Form target;

    Ref(const Loc &loc, const Form &target): 
      Form::Imp(loc), target(target) {}

    virtual void dump(ostream &out) const override {
      out << '&' << target;
    }

    virtual E emit(VM &vm, Env &env, Forms &args) const override;

    virtual E emit_call(VM &vm, 
			Env &env, 
			const Forms &args, 
			const Loc &loc) const override;
  };
}

#endif
