#ifndef CLAES_OPS_PUSH_REGISTER_HPP
#define CLAES_OPS_PUSH_REGISTER_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct PushRegister: Op::Imp {
    PushRegister(): Op::Imp(Op::Code::PUSH_REGISTER) {}
    
    virtual void trace(ostream &out) const override {
      out << "PushRegister";
    }
  };
}

#endif
