#ifndef CLAES_TYPES_BIT_HPP
#define CLAES_TYPES_BIT_HPP

#include <cstdint>
#include <ostream>
#include "claes/cell.hpp"
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

    virtual void dump(const Cell &value, ostream &out) const override {
      out << (value.as(get()) ? 'T' : 'F');
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
