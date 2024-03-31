#ifndef CLAES_OPS_RETURN_HPP
#define CLAES_OPS_RETURN_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Return: Op::Imp {
    Return():
      Op::Imp(Op::Code::RETURN) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "Return";
    }
  };
}

#endif
