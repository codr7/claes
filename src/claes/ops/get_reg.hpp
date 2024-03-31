#ifndef CLAES_OPS_GET_REG_HPP
#define CLAES_OPS_GET_REG_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"
#include "claes/reg.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct GetReg: Op::Imp {
    Reg reg;

    GetReg(const Reg &reg): Op::Imp(Op::Code::GET_REG), reg(reg) {}
    virtual void trace(VM &vm, ostream &out) const override;
  };
}

#endif
