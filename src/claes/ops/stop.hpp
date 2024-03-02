#ifndef CLAES_OPS_STOP_HPP
#define CLAES_OPS_STOP_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Stop: Op::Imp {
    Stop():
      Op::Imp(Op::Code::STOP) {}
  };
}

#endif
