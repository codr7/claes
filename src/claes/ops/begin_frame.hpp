#ifndef CLAES_OPS_BEGIN_FRAME_HPP
#define CLAES_OPS_BEGIN_FRAME_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct BeginFrame: Op::Imp {
    bool recursive;
    
    BeginFrame(bool recursive):
      Op::Imp(Op::Code::BEGIN_FRAME), recursive(recursive) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "BeginFrame";
    }
  };
}

#endif
