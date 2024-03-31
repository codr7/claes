#ifndef CLAES_OPS_DEREF_HPP
#define CLAES_OPS_DEREF_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Deref: Op::Imp {
    Deref():
      Op::Imp(Op::Code::DEREF) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "Deref";
    }
  };
}

#endif
