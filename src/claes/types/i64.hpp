#ifndef CLAES_TYPES_I64_HPP
#define CLAES_TYPES_I64_HPP

#include <cstdint>
#include <ostream>

#include "claes/cell.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct I64: Type::Imp {
    using Value = int64_t;

    static TType<I64> get() {
      static TType<I64> t("I64");
      return t;
    } 
    
    I64(const string &name): Type::Imp(name) {}

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return left.as(get()) <=> right.as(get());
    }

    virtual void dump(const Cell &value, ostream &out) const override {
      out << value.as(get());
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return left.as(get()) == right.as(get());
    }

    virtual bool is_true(const Cell &value) const override {
      return value.as(get()) != 0;
    }

    virtual Cell iter(const Cell &target) const override;

    virtual E js(const Cell &value, 
		 ostream &out, 
		 const claes::Loc &loc) const override {
      out << value.as(get());
      return nullopt;
    }
  };
}

#endif
