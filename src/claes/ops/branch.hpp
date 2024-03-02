#ifndef CLAES_OPS_BRANCH_HPP
#define CLAES_OPS_BRANCH_HPP

#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Branch: Op::Imp {
    PC else_pc;

    Branch(PC else_pc):
      Op::Imp(Op::Code::BRANCH), else_pc(else_pc) {}
  };
}

#endif
