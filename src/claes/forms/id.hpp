#ifndef CLAES_FORMS_ID_HPP
#define CLAES_FORMS_ID_HPP

#include "claes/form.hpp"

namespace claes::forms {
  struct Id: Form::Imp {
    static Form make(const Loc &loc, const string &name) {
      return Form::make<Id>(loc, name);
    };

    string name;

    Id(const Loc &loc, const string &name): 
      Form::Imp(loc), name(name) {}

    virtual void collect_ids(set<string> &out) const override {
      out.insert(name);
    }
    
    virtual void dump(ostream &out) const override {
      out << name;
    }

    virtual E emit(VM &vm, Env &env, Forms &arguments) const override;

    virtual E emit_call(VM &vm, 
			Env &env, 
			const Forms &arguments, 
			const Loc &loc) const override;

    virtual E emit_ref(VM &vm, 
		       Env &env, 
		       Forms &arguments, 
		       const Loc &loc) const override;

    pair<optional<Cell>, E> find(Env &env) const;

    E quote(VM &vm, Env &env, int depth) const override;
  };
}

#endif
