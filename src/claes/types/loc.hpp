#ifndef CLAES_TYPES_LOC_HPP
#define CLAES_TYPES_LOC_HPP

#include <cstdint>
#include <ostream>

#include "claes/cell.hpp"
#include "claes/loc.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Loc: Type::Imp {
    using Value = claes::Loc;

    static TType<Loc> get() {
      static TType<Loc> t("Loc");
      return t;
    } 
    
    Loc(const string &name): Type::Imp(name) {}

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
  };
}

#endif
