#ifndef CLAES_FORMS_LITERAL_HPP
#define CLAES_FORMS_LITERAL_HPP

#include "claes/form.hpp"
#include "claes/cell.hpp"

namespace claes::forms {
  struct Literal: Form::Imp {
    Cell value;
    
    Literal(const Loc &loc, const Cell &value): 
      Form::Imp(loc), value(value) {}

    virtual void collect_ids(set<string> &out) const override {}

    virtual void dump(ostream &out) const override {
      out << value;
    }

    virtual E emit(VM &vm, Env &env, Forms &arguments) const override {
      return value.emit_literal(vm, env, arguments, loc);
    }

    virtual E emit_call(VM &vm, 
			Env &env, 
			const Forms &arguments, 
			const Loc &loc) const override {
      return value.emit_call(vm, env, arguments, loc);
    }

    virtual Cell quote(VM &vm, int depth) const override;
  };
}

#endif
