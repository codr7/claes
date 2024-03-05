#ifndef CLAES_OPS_PUSH_ITEM_HPP
#define CLAES_OPS_PUSH_ITEM_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct PushItem: Op::Imp {
    PushItem():
      Op::Imp(Op::Code::PUSH_ITEM) {}

    virtual void trace(ostream &out) const override {
      out << "PushItem";
    }
  };
}

#endif
