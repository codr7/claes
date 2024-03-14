#ifndef CLAES_OPS_CALL_REG_HPP
#define CLAES_OPS_CALL_REG_HPP

#include "claes/op.hpp"
#include "claes/reg.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct CallReg: Op::Imp {
    Reg target_reg;
    int arity;
    Loc loc;

    CallReg(const Reg target_reg, int arity, const Loc &loc): 
      Op::Imp(Op::Code::CALL_REG), target_reg(target_reg), arity(arity), loc(loc) {}
    
    virtual void trace(ostream &out) const override {
      out << "CallReg target_reg: " << 
	target_reg << " arity: " << arity << " loc: " << loc;
    }
  };
}

#endif
