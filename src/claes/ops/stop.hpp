#ifndef CLAES_OPS_STOP_HPP
#define CLAES_OPS_STOP_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Stop: Op::Imp {
    Cell value;

    Stop(const Cell &value):
      Op::Imp(Op::Code::STOP), value(value) {}
  };
}

#endif
