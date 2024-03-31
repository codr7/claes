#ifndef CLAES_OPS_MAKE_VECTOR_HPP
#define CLAES_OPS_MAKE_VECTOR_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct MakeVector: Op::Imp {
    MakeVector():
      Op::Imp(Op::Code::MAKE_VECTOR) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "MakeVector";
    }
  };
}

#endif
