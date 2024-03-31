#include "claes/ops/call_reg.hpp"
#include "claes/vm.hpp"

namespace claes::ops {
   void CallReg::trace(VM &vm, ostream &out) const {
    Reg t = target_reg;
    t.frame_offset = vm.frame_offset(t);
    out << "CallReg target_reg: " << t << " arity: " << arity << " loc: " << loc;
  }
}
