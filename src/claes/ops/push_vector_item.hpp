#ifndef CLAES_OPS_PUSH_VECTOR_ITEM_HPP
#define CLAES_OPS_PUSH_VECTOR_ITEM_HPP

#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct PushVectorItem: Op::Imp {
    PushVectorItem():
      Op::Imp(Op::Code::PUSH_VECTOR_ITEM) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "PushVectorItem";
    }
  };
}

#endif
