#ifndef CLAES_OPS_DECREMENT_HPP
#define CLAES_OPS_DECREMENT_HPP

#include "claes/op.hpp"
#include "claes/reg.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Decrement: Op::Imp {
    Reg target_reg;
    
    Decrement(const Reg target_reg): 
      Op::Imp(Op::Code::DECREMENT), target_reg(target_reg) {}
    
    virtual void trace(VM &vm, ostream &out) const override;
  };
}

#endif
