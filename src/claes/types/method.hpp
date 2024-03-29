#ifndef CLAES_TYPES_METHOD_HPP
#define CLAES_TYPES_METHOD_HPP

#include <cstdint>
#include <ostream>
#include "claes/method.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Method: Type::Imp {
    using Value = claes::Method;

    static TType<Method> get() {
      static TType<Method> t("Method");
      return t;
    }
    
    Method(const string &name): Type::Imp(name) {}

    virtual E call(Cell &target, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const claes::Loc &loc) const override;

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
