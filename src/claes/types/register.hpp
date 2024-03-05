#ifndef CLAES_TYPES_REGISTER_HPP
#define CLAES_TYPES_REGISTER_HPP

#include <cstdint>
#include <ostream>
#include "claes/register.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Register: Type::Imp {
    using Value = claes::Register;

    static TType<Register> get() {
      static TType<Register> t("Register");
      return t;
    }
    
    Register(const string &name): Type::Imp(name) {}

    virtual void dump(const Cell &value, ostream &out) const override;

    virtual E emit_id(const Cell &value,
		      VM &vm, 
		      Env &env, 
		      Forms &arguments,
		      const Loc &loc) const override;
    
    virtual bool eq(const Cell &left, const Cell &right) const override;
  };
}

#endif
