#ifndef CLAES_OPS_DECREMENT_HPP
#define CLAES_OPS_DECREMENT_HPP

#include "claes/op.hpp"
#include "claes/reg.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Decrement: Op::Imp {
    Reg target_reg;
    types::I64::Value delta;
    
    Decrement(const Reg target_reg, types::I64::Value delta): 
      Op::Imp(Op::Code::DECREMENT), target_reg(target_reg), delta(delta) {}
    
    virtual void trace(ostream &out) const override {
      out << "Decrement target_reg: " << target_reg << " delta: " << delta;
    }
  };
}

#endif
