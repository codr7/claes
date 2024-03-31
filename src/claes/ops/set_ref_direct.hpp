#ifndef CLAES_OPS_SET_REF_DIRECT_HPP
#define CLAES_OPS_SET_REF_DIRECT_HPP

#include "claes/op.hpp"
#include "claes/ref.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct SetRefDirect: Op::Imp {
    Ref target;

    SetRefDirect(const Ref &target): 
      Op::Imp(Op::Code::SET_REF_DIRECT), target(target) {}
    
    virtual void trace(VM &vm, ostream &out) const override {
      out << "SetRefDirect target: " << target;
    }
  };
}

#endif
