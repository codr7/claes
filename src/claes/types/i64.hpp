#ifndef CLAES_TYPES_I64_HPP
#define CLAES_TYPES_I64_HPP

#include <cstdint>
#include "claes/cell.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct I64: Type::Imp {
    using Value = int64_t;
    
    I64(const string &name): Type::Imp(name) {}

    virtual void dump(const Cell &value, ostream &out) const override {
      out << value.as<Value>();
    }
    
    virtual bool is_true(const Cell &value) const override {
      return value.as<Value>() != 0;
    }
  };

  static TType<I64> i64("i64"); 
}

#endif
