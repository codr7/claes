#ifndef CLAES_OPS_FOR_HPP
#define CLAES_OPS_FOR_HPP

#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct For: Op::Imp {
    PC end_pc;

    For(const PC &end_pc):
      Op::Imp(Op::Code::FOR), end_pc(end_pc) {}
    
    virtual void trace(VM &vm, ostream &out) const override {
      out << "For end_pc: " << end_pc;
    }
  };
}

#endif
