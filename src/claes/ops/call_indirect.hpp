#ifndef CLAES_OPS_CALL_INDIRECT_HPP
#define CLAES_OPS_CALL_INDIRECT_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct CallIndirect: Op::Imp {
    Location location;

    CallIndirect(const Location &location):
      Op::Imp(Op::Code::CALL_INDIRECT), location(location) {}

    virtual void trace(ostream &out) const override {
      out << "CallIndirect location: " << location;
    }
  };
}

#endif
