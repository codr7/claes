#ifndef CLAES_TYPES_REF_HPP
#define CLAES_TYPES_REF_HPP

#include "claes/cell.hpp"
#include "claes/ref.hpp"

namespace claes::types {
  using namespace claes;

  struct Ref: Type::Imp {
    using Value = claes::Ref;
    
    static TType<Ref> get() {
      static TType<Ref> t("Ref");
      return t;
    }    

    Ref(const string &name): Type::Imp(name) {}

    virtual E call(const Cell &target, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   const Loc &loc) const override;

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return left.as(get()).imp->value <=> right.as(get()).imp->value;
    }

    virtual void dump(const Cell &value, ostream &out) const override {
      out << '&' << value.as(get()).imp->value;
    }

    virtual E emit_call(const Cell &value,
			VM &vm, 
			Env &env, 
			const Forms &args,
			const Loc &loc) const override;

    virtual bool eq(const Cell &left, const Cell &right) const override {      
      const auto &lv = left.as(get()), &rv = right.as(get());
      return lv.imp->value == rv.imp->value;
    }
  };
}

#endif
