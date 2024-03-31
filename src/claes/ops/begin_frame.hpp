#ifndef CLAES_OPS_BEGIN_FRAME_HPP
#define CLAES_OPS_BEGIN_FRAME_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct BeginFrame: Op::Imp {
    BeginFrame():
      Op::Imp(Op::Code::BEGIN_FRAME) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "BeginFrame";
    }
  };
}

#endif
