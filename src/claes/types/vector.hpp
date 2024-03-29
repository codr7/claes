#ifndef CLAES_TYPES_VECTOR_HPP
#define CLAES_TYPES_VECTOR_HPP

#include <vector>
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Vector: Type::Imp {
    using Value = vector<Cell>;
    
    static TType<Vector> get() {
      static TType<Vector> t("Vector");
      return t;
    }    

    Vector(const string &name): Type::Imp(name) {}
    
    virtual E call(VM &vm, 
		   Stack &stack, 
		   int arity,
		   const claes::Loc &loc) const override;

    virtual E call(Cell &target, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const claes::Loc &loc) const override;

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override;

    virtual void dump(const Cell &value, ostream &out) const override;
    virtual bool eq(const Cell &left, const Cell &right) const override;
    virtual bool is_true(const Cell &value) const override;
    virtual Cell iter(const Cell &target) const override;

    virtual E js(const Cell &value, 
		 ostream &out, const 
		 claes::Loc &loc) const override;

    virtual void push(Cell &target, const Cell &item) const override;
  };
}

#endif
