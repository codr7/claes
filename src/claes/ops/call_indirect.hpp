#ifndef CLAES_OPS_CALL_INDIRECT_HPP
#define CLAES_OPS_CALL_INDIRECT_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct CallIndirect: Op::Imp {
    int arity;
    Loc loc;

    CallIndirect(int arity, const Loc &loc):
      Op::Imp(Op::Code::CALL_INDIRECT), arity(arity), loc(loc) {}

    virtual void trace(ostream &out) const override {
      out << "CallIndirect arity: " << arity << " loc: " << loc;
    }
  };
}

#endif
