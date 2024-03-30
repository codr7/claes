#ifndef CLAES_OPS_PUSH_MAP_ITEM_HPP
#define CLAES_OPS_PUSH_MAP_ITEM_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct PushMapItem: Op::Imp {
    PushMapItem():
      Op::Imp(Op::Code::PUSH_MAP_ITEM) {}

    virtual void trace(ostream &out) const override {
      out << "PushMapItem";
    }
  };
}

#endif
