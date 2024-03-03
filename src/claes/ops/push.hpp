#ifndef CLAES_OPS_PUSH_HPP
#define CLAES_OPS_PUSH_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Push: Op::Imp {
    Cell value;

    Push(const Cell &value):
      Op::Imp(Op::Code::PUSH), value(value) {}
    
    virtual void trace(ostream &out) const override {
      out << "Push value: " << value;
    }
  };
}

#endif
