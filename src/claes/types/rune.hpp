#ifndef CLAES_TYPES_RUNE_HPP
#define CLAES_TYPES_RUNE_HPP

#include <cstdint>
#include "claes/cell.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Rune: Type::Imp {
    using Value = char;
    
    static TType<Rune> get() {
      static TType<Rune> t("Rune");
      return t;
    }    

    Rune(const string &name): Type::Imp(name) {}

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return left.as(get()) <=> right.as(get());
    }

    virtual void dump(const Cell &value, ostream &out) const override {
      out << '\\' << value.as(get());
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return left.as(get()) == right.as(get());
    }

    virtual bool is_true(const Cell &value) const override {
      return value.as(get());
    }
  };
}

#endif
