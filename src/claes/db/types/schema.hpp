#ifdef USE_SQLITE
#pragma once

#include <cstdint>
#include <ostream>

#include "claes/db/schema.hpp"
#include "claes/type.hpp"

namespace claes::db::types {
  using namespace claes;

  struct Schema: Type::Imp {
    using Value = db::Schema;

    static TType<Schema> get() {
      static TType<Schema> t("Schema");
      return t;
    }
    
    Schema(const string &name): Type::Imp(name) {}

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return &left.as(get()) <=> &right.as(get());
    }
    
    virtual void dump(const Cell &value, ostream &out) const override;

    virtual claes::E emit_call(const Cell &value,
			       VM &vm, 
			       Env &env, 
			       const Forms &args,
			       const claes::Loc &loc) const override;

    virtual bool eq(const Cell &left, const Cell &right) const override;
  };
}

#endif
