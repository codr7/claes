#ifndef CLAES_OPS_TAIL_CALL_HPP
#define CLAES_OPS_TAIL_CALL_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct TailCall: Op::Imp {
    PC start_pc;
    int reg_count;

    TailCall(PC start_pc, int reg_count):
      Op::Imp(Op::Code::TAIL_CALL), start_pc(start_pc), reg_count(reg_count) {}

    virtual void trace(VM &vm, ostream &out) const override;
  };
}

#endif
