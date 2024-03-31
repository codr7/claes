#ifndef CLAES_OPS_RECALL_HPP
#define CLAES_OPS_RECALL_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Recall: Op::Imp {
    int arity;
    claes::Loc loc;

    Recall(int arity, const claes::Loc &loc):
      Op::Imp(Op::Code::RECALL), arity(arity), loc(loc) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "Recall arity: " << arity << " loc: " << loc;
    }
  };
}

#endif
