#include "claes/ops/get_reg.hpp"
#include "claes/vm.hpp"

namespace claes::ops {
  void GetReg::trace(VM &vm, ostream &out) const {
    Reg v = reg;
    v.frame_offset = vm.frame_offset(v);
    out << "GetReg reg: " << v;
  }
}
