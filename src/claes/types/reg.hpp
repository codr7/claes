#ifndef CLAES_TYPES_REG_HPP
#define CLAES_TYPES_REG_HPP

#include <cstdint>
#include <ostream>
#include "claes/reg.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Reg: Type::Imp {
    using Value = claes::Reg;

    static TType<Reg> get() {
      static TType<Reg> t("Reg");
      return t;
    }
    
    Reg(const string &name): Type::Imp(name) {}

    virtual void dump(const Cell &value, ostream &out) const override;

    virtual E emit_id(const Cell &value,
		      VM &vm, 
		      Env &env, 
		      Forms &args,
		      const Loc &loc) const override;
    
    virtual bool eq(const Cell &left, const Cell &right) const override;
  };
}

#endif
