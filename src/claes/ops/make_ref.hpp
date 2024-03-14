#ifndef CLAES_OPS_MAKE_REF_HPP
#define CLAES_OPS_MAKE_REF_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct MakeRef: Op::Imp {
    MakeRef():
      Op::Imp(Op::Code::MAKE_REF) {}

    virtual void trace(ostream &out) const override {
      out << "MakeRef";
    }
  };
}

#endif
