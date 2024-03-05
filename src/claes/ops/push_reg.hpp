#ifndef CLAES_OPS_PUSH_REG_HPP
#define CLAES_OPS_PUSH_REG_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct PushReg: Op::Imp {
    PushReg(): Op::Imp(Op::Code::PUSH_REG) {}
    
    virtual void trace(ostream &out) const override {
      out << "PushReg";
    }
  };
}

#endif
