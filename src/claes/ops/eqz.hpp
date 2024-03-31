#ifndef CLAES_OPS_EQZ_HPP
#define CLAES_OPS_EQZ_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Eqz: Op::Imp {
    Eqz():
      Op::Imp(Op::Code::ZERO) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "Eqz";
    }
  };
}

#endif
