#ifndef CLAES_CALL_HPP
#define CLAES_CALL_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"

namespace claes {
  struct Call {
    Call *parent;
    Cell target;
    Loc loc;
    PC ret_pc;

    Call(Call *parent, const Cell &target, const Loc &loc, const PC ret_pc):
      parent(parent), target(target), loc(loc), ret_pc(ret_pc) {}
  };
}

#endif
