#ifndef CLAES_FORMS_PAIR_HPP
#define CLAES_FORMS_PAIR_HPP

#include "claes/form.hpp"

namespace claes::forms {
  struct Pair: Form::Imp {
    static Form make(const Loc &loc, 
		     const Form &left, 
		     const Form &right) {
      return Form::make<Pair>(loc, left, right);
    };

    Form left, right;

    Pair(const Loc &loc, const Form &left, const Form &right): 
      Form::Imp(loc), left(left), right(right) {}

    virtual E emit(VM &vm, Env &env, Forms &args) const;
  };
}

#endif
