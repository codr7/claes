#ifndef CLAES_OPS_TODO_HPP
#define CLAES_OPS_TODO_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Todo: Op::Imp {
    Location location;

    Todo(const Location &location):
      Op::Imp(Op::Code::TODO), location(location) {}

    virtual void trace(ostream &out) const override {
      out << "Todo location: " << location;
    }
  };
}

#endif
