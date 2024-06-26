#ifndef CLAES_TYPES_LIB_HPP
#define CLAES_TYPES_LIB_HPP

#include <ostream>
#include "claes/env.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Lib: Type::Imp {
    using Value = claes::Env *;

    static TType<Lib> get() {
      static TType<Lib> t("Lib");
      return t;
    }
    
    Lib(const string &name): Type::Imp(name) {}

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return left.as(get()) <=> right.as(get());
    }
    
    virtual void dump(const Cell &value, ostream &out) const override;
    virtual bool eq(const Cell &left, const Cell &right) const override;
  };
}

#endif
