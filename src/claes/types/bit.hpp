#ifndef CLAES_TYPES_BIT_HPP
#define CLAES_TYPES_BIT_HPP

#include <cstdint>
#include <ostream>
#include "claes/cell.hpp"
#include "claes/stack.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Bit: Type::Imp {
    using Value = bool;

    static TType<Bit> get() {
      static TType<Bit> t("Bit");
      return t;
    }
    
    Bit(const string &name): Type::Imp(name) {}

    virtual E call(VM &vm, 
		   Stack &stack, 
		   int arity,
		   const Loc &loc) const override {
      auto &v = stack.peek();
      v = Cell(get(), v.is_true());
      return nullopt;
    }

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return left.as(get()) <=> right.as(get());
    }
    
    virtual void dump(const Cell &value, ostream &out) const override {
      out << (value.as(get()) ? 'T' : 'F');
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return left.as(get()) == right.as(get());
    }

    virtual bool is_true(const Cell &value) const override {
      return value.as(get());
    }

    virtual E js(const Cell &value, 
		 ostream &out, 
		 const claes::Loc &loc) const override {
      out << (value.as(get()) ? "true" : "false");
      return nullopt;
    }
  };
}

#endif
