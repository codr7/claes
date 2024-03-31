#ifndef CLAES_OPS_TODO_HPP
#define CLAES_OPS_TODO_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Todo: Op::Imp {
    claes::Loc loc;

    Todo(const claes::Loc &loc):
      Op::Imp(Op::Code::TODO), loc(loc) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "Todo loc: " << loc;
    }
  };
}

#endif
