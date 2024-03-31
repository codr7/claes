#ifndef CLAES_OPS_PUSH_REGS_HPP
#define CLAES_OPS_PUSH_REGS_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct PushRegs: Op::Imp {
    int n;
    
    PushRegs(const int n): Op::Imp(Op::Code::PUSH_REGS), n(n) {}
    
    virtual void trace(VM &vm, ostream &out) const override {
      out << "PushRegs n: " << n;
    }
  };
}

#endif
