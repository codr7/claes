#ifndef CLAES_TYPES_BIT_HPP
#define CLAES_TYPES_BIT_HPP

#include <cstdint>
#include <ostream>
#include "claes/cell.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Bit: Type::Imp {
    static TType<Bit> type;
    using Value = bool;
    
    Bit(const string &name): Type::Imp(name) {}

    virtual void dump(const Cell &value, ostream &out) const override {
      out << (value.as(type) ? 'T' : 'F');
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return left.as(type) == right.as(type);
    }

    virtual bool is_true(const Cell &value) const override {
      return value.as(type);
    }
  };

  static TType<Bit> &bit(Bit::type);
}

#endif
