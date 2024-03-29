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

    virtual E call(Cell &target, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const claes::Loc &loc) const override;

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return left.as(get()) <=> right.as(get());
    }

    virtual void dump(const Cell &value, ostream &out) const override {
      out << value.as(get());
    }

    virtual E emit_call(const Cell &value,
			VM &vm, 
			Env &env, 
			const Forms &args,
			const claes::Loc &loc) const override;

    virtual bool eq(const Cell &left, const Cell &right) const override {      
      return left.as(get()) == right.as(get());
    }
  };
}

#endif
