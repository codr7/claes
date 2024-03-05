#ifndef CLAES_OPS_END_FRAME_HPP
#define CLAES_OPS_END_FRAME_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct EndFrame: Op::Imp {
    EndFrame():
      Op::Imp(Op::Code::END_FRAME) {}

    virtual void trace(ostream &out) const override {
      out << "EndFrame";
    }
  };
}

#endif
