#ifndef CLAES_OPS_STOP_HPP
#define CLAES_OPS_STOP_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Stop: Op::Imp {
    claes::Loc loc;

    Stop(const claes::Loc &loc):
      Op::Imp(Op::Code::STOP), loc(loc) {}

    virtual void trace(ostream &out) const override {
      out << "Stop loc: " << loc;
    }
  };
}

#endif
