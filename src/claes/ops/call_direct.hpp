#ifndef CLAES_OPS_CALL_DIRECT_HPP
#define CLAES_OPS_CALL_DIRECT_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct CallDirect: Op::Imp {
    Cell target;
    int arity;
    Loc loc;

    CallDirect(const Cell &target, int arity, const Loc &loc):
      Op::Imp(Op::Code::CALL_DIRECT), target(target), arity(arity), loc(loc) {}

    virtual void trace(ostream &out) const override {
      out << "CallDirect target: " << target << " arity: " << arity << " loc: " << 
	loc;
    }
  };
}

#endif
