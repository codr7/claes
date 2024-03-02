#ifndef CLAES_TYPES_I64_HPP
#define CLAES_TYPES_I64_HPP

#include <cstdint>
#include <ostream>

#include "claes/cell.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct I64: Type::Imp {
    static TType<I64> type; 
    using Value = int64_t;
    
    I64(const string &name): Type::Imp(name) {}

    virtual void dump(const Cell &value, ostream &out) const override {
      out << value.as(type);
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return left.as(type) == right.as(type);
    }

    virtual bool is_true(const Cell &value) const override {
      return value.as(type) != 0;
    }
  };

  static TType<I64> &i64(I64::type);
}

#endif
