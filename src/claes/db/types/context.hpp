#ifdef USE_CONTEXT
#pragma once

#include <cstdint>
#include <ostream>

#include "claes/context.hpp"
#include "claes/type.hpp"

namespace claes::db::types {
  using namespace claes;

  struct Context: Type::Imp {
    using Value = claes::Context;

    static TType<Context> get() {
      static TType<Context> t("Context");
      return t;
    }
    
    Context(const string &name): Type::Imp(name) {}

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return &left.as(get()) <=> &right.as(get());
    }
    
    virtual void dump(const Cell &value, ostream &out) const override;
    virtual bool eq(const Cell &left, const Cell &right) const override;
  };
}

#endif
