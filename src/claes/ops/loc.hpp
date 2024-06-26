#ifndef CLAES_OPS_LOC_HPP
#define CLAES_OPS_LOC_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Loc: Op::Imp {
    claes::Loc loc;

    Loc(const claes::Loc &loc):
      Op::Imp(Op::Code::LOC), loc(loc) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "Loc " << loc;
    }
  };
}

#endif
