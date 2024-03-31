#ifndef CLAES_OPS_SPLAT_HPP
#define CLAES_OPS_SPLAT_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Splat: Op::Imp {
    Splat():
      Op::Imp(Op::Code::SPLAT) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "Splat";
    }
  };
}

#endif
