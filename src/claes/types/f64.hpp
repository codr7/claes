#pragma once

#include <cstdint>
#include <ostream>

#include "claes/cell.hpp"
#include "claes/f64.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;
  using namespace std;

  struct F64: Type::Imp {
    using Value = f64::T;

    static TType<F64> get() {
      static TType<F64> t("F64");
      return t;
    } 
    
    F64(const string &name): Type::Imp(name) {}

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return f64::val(left.as(get())) <=> f64::val(right.as(get()));
    }

    virtual void dump(const Cell &value, ostream &out) const override {
      f64::print(value.as(get()), out);
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return f64::val(left.as(get())) == f64::val(right.as(get()));
    }

    virtual bool is_true(const Cell &value) const override {
      return f64::val(value.as(get())) != 0;
    }
  };
}

