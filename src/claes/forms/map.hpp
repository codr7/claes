#pragma once

#include "claes/form.hpp"
#include "claes/forms.hpp"

namespace claes::forms {
  struct Map: Form::Imp {
    static Form make(const Loc &loc, const Forms items) {
      return Form::make<Map>(loc, items);
    };

    Forms items;

    Map(const Loc &loc, const Forms items): Form::Imp(loc), items(items) {}

    virtual void collect_ids(set<string> &out) const override {
      items.collect_ids(out);
    }

    virtual void dump(ostream &out) const override {
      out << '{' << items << '}';
    }

    virtual E emit(VM &vm, Env &env, Forms &arguments) const override;
    virtual E quote(VM &vm, Env &env, int depth) const override;
  };
}
