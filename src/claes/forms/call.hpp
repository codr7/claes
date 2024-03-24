#ifndef CLAES_FORMS_CALL_HPP
#define CLAES_FORMS_CALL_HPP

#include "claes/form.hpp"
#include "claes/forms.hpp"

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

    virtual void collect_ids(set<string> &out) const override {
      target.collect_ids(out);
      args.collect_ids(out);
    }

    virtual void dump(ostream &out) const override {
      out << '(' << target;

      if (!args.empty()) {
	out << ' ' << args;
      }
      
      out << ')';
    }

    virtual E emit(VM &vm, Env &env, Forms &args) const override {
      return target.emit_call(vm, env, this->args, loc);
    }

    virtual Cell quote(VM &vm, int depth) const override;
  };
}

#endif
