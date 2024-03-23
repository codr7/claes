#ifndef CLAES_CALL_HPP
#define CLAES_CALL_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"

namespace claes {
  struct Call {
    Loc loc;
    Call *parent;
    bool recursive;
    PC ret_pc;
    Cell target;

    Call(Call *parent, 
	 const Cell &target, 
	 bool recursive, 
	 const Loc &loc, 
	 const PC ret_pc):
      loc(loc), parent(parent), recursive(recursive), ret_pc(ret_pc), 
      target(target) {}
  };
}

#endif
