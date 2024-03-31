#ifndef CLAES_OPS_MAKE_MAP_HPP
#define CLAES_OPS_MAKE_MAP_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct MakeMap: Op::Imp {
    MakeMap():
      Op::Imp(Op::Code::MAKE_MAP) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "MakeMap";
    }
  };
}

#endif
