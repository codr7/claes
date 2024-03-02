#ifndef CLAES_TYPES_BIT_HPP
#define CLAES_TYPES_BIT_HPP

#include <cstdint>
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Bit: Type::Imp {
    using Value = bool;
    
    Bit(const string &name): Type::Imp(name) {}

    virtual void dump(const Cell &value, ostream &out) const override {
      out << value.as<Value>();
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return left.as<Value>() == right.as<Value>();
    }

    virtual bool is_true(const Cell &value) const override {
      return value.as<Value>();
    }
  };

  static TType<Bit> bit("bit"); 
}

#endif
