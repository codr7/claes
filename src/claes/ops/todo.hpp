#ifndef CLAES_OPS_TODO_HPP
#define CLAES_OPS_TODO_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Todo: Op::Imp {
    Loc loc;

    Todo(const Loc &loc):
      Op::Imp(Op::Code::TODO), loc(loc) {}

    virtual void trace(ostream &out) const override {
      out << "Todo loc: " << loc;
    }
  };
}

#endif
