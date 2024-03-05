#ifndef CLAES_OPS_MAKE_PAIR_HPP
#define CLAES_OPS_MAKE_PAIR_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct MakePair: Op::Imp {
    MakePair():
      Op::Imp(Op::Code::MAKE_PAIR) {}

    virtual void trace(ostream &out) const override {
      out << "MakePair";
    }
  };
}

#endif
