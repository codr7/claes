#include "claes/ops/set_reg.hpp"
#include "claes/vm.hpp"

namespace claes::ops {
  void SetReg::trace(VM &vm, ostream &out) const {
    Reg v = reg;
    v.frame_offset = vm.frame_offset(v);
    out << "SetReg reg: " << v;
  }
}
