#ifndef CLAES_TYPES_MACRO_HPP
#define CLAES_TYPES_MACRO_HPP

#include <cstdint>
#include <ostream>
#include "claes/macro.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Macro: Type::Imp {
    using Value = claes::Macro;

    static TType<Macro> get() {
      static TType<Macro> t("Macro");
      return t;
    }
    
    Macro(const string &name): Type::Imp(name) {}

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return left.as(get()) <=> right.as(get());
    }
    
    virtual void dump(const Cell &value, ostream &out) const override;
    
    virtual E emit_call(const Cell &value,
			VM &vm, 
			Env &env, 
			const Forms &args,
			const claes::Loc &loc) const override;

    virtual E emit_ref(const Cell &value,
		       VM &vm, 
		       Env &env, 
		       Forms &args,
		       const claes::Loc &loc) const override;

    virtual bool eq(const Cell &left, const Cell &right) const override;
  };
}

#endif
