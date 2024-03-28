#pragma once

#include <cstdint>
#include <ostream>

#include "claes/curl.hpp"
#include "claes/type.hpp"


namespace claes::types {
  using namespace claes;

  struct Curl: Type::Imp {
    using Value = claes::Curl;

    static TType<Curl> get() {
      static TType<Curl> t("Curl");
      return t;
    }
    
    Curl(const string &name): Type::Imp(name) {}

    virtual E call(VM &vm, 
		   Stack &stack, 
		   int arity,
		   const claes::Loc &loc) const override;

    virtual E call(Cell &target, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const claes::Loc &loc) const override;

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return &left.as(get()) <=> &right.as(get());
    }
    
    virtual void dump(const Cell &value, ostream &out) const override;
    
    virtual bool eq(const Cell &left, const Cell &right) const override;
  };
}
