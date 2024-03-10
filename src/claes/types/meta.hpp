#ifndef CLAES_TYPES_META_HPP
#define CLAES_TYPES_META_HPP

#include <ostream>
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Meta: Type::Imp {
    static TType<Meta> get() {
      static TType<Meta> t("Meta");
      return t;
    }

    using Value = claes::Type;
    
    Meta(const string &name): Type::Imp(name) {}

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return left.as(get()) <=> right.as(get());
    }

    virtual void dump(const Cell &value, ostream &out) const override;
    
    virtual bool eq(const Cell &left, const Cell &right) const override;
  };
}

#endif
