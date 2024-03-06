#ifndef CLAES_OPS_CHECK_HPP
#define CLAES_OPS_CHECK_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Check: Op::Imp {
    Loc loc;

    Check(const Loc &loc):
      Op::Imp(Op::Code::CHECK), loc(loc) {}
    
    virtual void trace(ostream &out) const override {
      out << "Check loc: " << loc;
    }
  };
}

#endif
