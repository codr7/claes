#ifndef CLAES_OPS_GOTO_HPP
#define CLAES_OPS_GOTO_HPP

#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Goto: Op::Imp {
    PC pc;

    Goto(const PC &pc):
      Op::Imp(Op::Code::GOTO), pc(pc) {}
    
    virtual void trace(ostream &out) const override {
      out << "Goto pc: " << pc;
    }
  };
}

#endif
