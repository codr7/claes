#ifndef CLAES_OPS_PUSH_VALUES_HPP
#define CLAES_OPS_PUSH_VALUES_HPP

#include "claes/common.hpp"
#include "claes/op.hpp"
#include "claes/reg.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct PushValues: Op::Imp {
    Reg target_reg;
    int n;
    
    PushValues(const Reg target_reg, int n): 
      Op::Imp(Op::Code::PUSH_VALUES), target_reg(target_reg), n(n) {}
    
    virtual void trace(VM &vm, ostream &out) const override;
  };
}

#endif
