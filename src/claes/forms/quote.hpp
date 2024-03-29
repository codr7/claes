#ifndef CLAES_FORMS_QUOTE_HPP
#define CLAES_FORMS_QUOTE_HPP

#include "claes/form.hpp"

namespace claes::forms {
  struct Quote: Form::Imp {
    static Form make(const Loc &loc, const Form &target) {
      return Form::make<Quote>(loc, target);
    }

    Form target;

    Quote(const Loc &loc, const Form &target): 
      Form::Imp(loc), target(target) {}

    virtual void collect_ids(set<string> &out) const override {
      target.collect_ids(out);
    }

    virtual void dump(ostream &out) const override {
      out << '\'' << target;
    }

    virtual E emit(VM &vm, Env &env, Forms &args) const override;

    virtual E quote(VM &vm, Env &env, int depth) const override;
  };
}

#endif
