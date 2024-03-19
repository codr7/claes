#ifndef CLAES_TYPES_ITER_HPP
#define CLAES_TYPES_ITER_HPP

#include "claes/cell.hpp"
#include "claes/iter.hpp"

namespace claes::types {
  using namespace claes;

  struct Iter: Type::Imp {
    using Value = claes::Iter;
    
    static TType<Iter> get() {
      static TType<Iter> t("Iter");
      return t;
    }    

    Iter(const string &name): Type::Imp(name) {}

    virtual E call(Cell &target, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   const Loc &loc) const override;

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return left.as(get()) <=> right.as(get());
    }

    virtual void dump(const Cell &value, ostream &out) const override {
      out << value.as(get());
    }

    virtual bool eq(const Cell &left, const Cell &right) const override {      
      return left.as(get()) == right.as(get());
    }
  };
}

#endif
