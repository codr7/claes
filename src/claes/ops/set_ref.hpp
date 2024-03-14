#ifndef CLAES_OPS_SET_REF_HPP
#define CLAES_OPS_SET_REF_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct SetRef: Op::Imp {
    SetRef(): Op::Imp(Op::Code::SET_REF) {}
    
    virtual void trace(ostream &out) const override {
      out << "SetRef";
    }
  };
}

#endif
