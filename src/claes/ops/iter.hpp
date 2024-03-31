#ifndef CLAES_OPS_ITER_HPP
#define CLAES_OPS_ITER_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Iter: Op::Imp {
    Iter():
      Op::Imp(Op::Code::ITER) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "Iter";
    }
  };
}

#endif
