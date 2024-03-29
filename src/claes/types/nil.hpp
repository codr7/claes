#ifndef CLAES_TYPES_NIL_HPP
#define CLAES_TYPES_NIL_HPP

#include <cstdint>
#include <ostream>

#include "claes/cell.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Nil: Type::Imp {
    using Value = bool;

    static TType<Nil> get() {
      static TType<Nil> t("Nil");
      return t;
    }
    
    Nil(const string &name): Type::Imp(name) {}

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return left.as(get()) <=> right.as(get());
    }

    virtual void dump(const Cell &value, ostream &out) const override {
      out << '_';
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return true;
    }

    virtual bool is_true(const Cell &value) const override {
      return false;
    }

    virtual E js(const Cell &value, 
		 ostream &out, 
		 const claes::Loc &loc) const override {
      out << "null";
      return nullopt;
    }

    virtual void push(Cell &target, const Cell &item) const override {
      target = item;
    }
  };
}

#endif
