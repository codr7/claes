#ifndef CLAES_OPS_EXIT_HPP
#define CLAES_OPS_EXIT_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Exit: Op::Imp {
    Exit():
      Op::Imp(Op::Code::EXIT) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "Exit";
    }
  };
}

#endif
