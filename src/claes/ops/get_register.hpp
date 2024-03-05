#ifndef CLAES_OPS_GET_REGISTER_HPP
#define CLAES_OPS_GET_REGISTER_HPP

#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"
#include "claes/register.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct GetRegister: Op::Imp {
    Register reg;

    GetRegister(const Register &reg): Op::Imp(Op::Code::GET_REGISTER), reg(reg) {}
    
    virtual void trace(ostream &out) const override {
      out << "GetRegister reg: " << reg;
    }
  };
}

#endif
