#ifndef CLAES_VM_HPP
#define CLAES_VM_HPP

#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes {
  struct Error;
  struct Stack;

  struct VM {
    PC pc = 0;
    vector<Op> ops;

    optional<Error> eval(PC start_pc, Stack &stack);
  };
}

#endif
