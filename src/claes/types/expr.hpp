#ifndef CLAES_TYPES_EXPR_HPP
#define CLAES_TYPES_EXPR_HPP

#include "claes/cell.hpp"
#include "claes/expr.hpp"

namespace claes::types {
  using namespace claes;

  struct Expr: Type::Imp {
    using Value = claes::Expr;
    
    static TType<Expr> get() {
      static TType<Expr> t("Expr");
      return t;
    }    

    Expr(const string &name): Type::Imp(name) {}

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

    virtual bool eq(const Cell &left, const Cell &right) const override {      
      return left.as(get()) == right.as(get());
    }
  };
}

#endif
