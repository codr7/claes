#ifndef CLAES_OPS_RECALL_HPP
#define CLAES_OPS_RECALL_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Recall: Op::Imp {
    int arity;
    Loc loc;

    Recall(int arity, const Loc &loc):
      Op::Imp(Op::Code::RECALL), arity(arity), loc(loc) {}

    virtual void trace(ostream &out) const override {
      out << "Recall arity: " << arity << " loc: " << loc;
    }
  };
}

#endif
