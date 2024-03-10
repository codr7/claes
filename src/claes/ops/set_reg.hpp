#ifndef CLAES_OPS_SET_REG_HPP
#define CLAES_OPS_SET_REG_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"
#include "claes/reg.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct SetReg: Op::Imp {
    Reg reg;

    SetReg(const Reg &reg): Op::Imp(Op::Code::SET_REG), reg(reg) {}
    
    virtual void trace(ostream &out) const override {
      out << "SetReg reg: " << reg;
    }
  };
}

#endif
