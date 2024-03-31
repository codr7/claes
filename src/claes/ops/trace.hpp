#ifndef CLAES_OPS_TRACE_HPP
#define CLAES_OPS_TRACE_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Trace: Op::Imp {
    Trace():
      Op::Imp(Op::Code::TRACE) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "Trace";
    }
  };
}

#endif
