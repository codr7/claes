#ifndef CLAES_OPS_SET_REF_HPP
#define CLAES_OPS_SET_REF_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct SetRef: Op::Imp {
    Reg target_reg;

    SetRef(Reg target_reg): Op::Imp(Op::Code::SET_REF), target_reg(target_reg) {}
    
    virtual void trace(ostream &out) const override {
      out << "SetRef";
    }
  };
}

#endif
