#ifndef CLAES_FORMS_VECTOR_HPP
#define CLAES_FORMS_VECTOR_HPP

#include "claes/form.hpp"
#include "claes/forms.hpp"

namespace claes::forms {
  struct Vector: Form::Imp {
    static Form make(const Loc &loc, const Forms items) {
      return Form::make<Vector>(loc, items);
    };

    Forms items;

    Vector(const Loc &loc, const Forms items): Form::Imp(loc), items(items) {}

    virtual void collect_ids(set<string> &out) const override {
      items.collect_ids(out);
    }

    virtual void dump(ostream &out) const override {
      out << '[' << items << ']';
    }

    virtual E emit(VM &vm, Env &env, Forms &arguments) const override;
    virtual Cell quote(VM &vm, int depth) const override;
  };
}

#endif
