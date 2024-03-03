#ifndef CLAES_TYPES_STRING_HPP
#define CLAES_TYPES_STRING_HPP

#include <cstdint>
#include "claes/cell.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct String: Type::Imp {
    static TType<String> type;
    using Value = string;
    
    String(const string &name): Type::Imp(name) {}

    virtual void dump(const Cell &value, ostream &out) const override {
      out << '"' << value.as(type) << '"';
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return left.as(type) == right.as(type);
    }

    virtual bool is_true(const Cell &value) const override {
      return !value.as(type).empty();
    }
  };

  static TType<String> &string(String::type);
}

#endif
