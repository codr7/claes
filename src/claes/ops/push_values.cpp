#include "claes/ops/push_values.hpp"
#include "claes/vm.hpp"

namespace claes::ops {
  void PushValues::trace(VM &vm, ostream &out) const {
    Reg t = target_reg;
    t.frame_offset = vm.frame_offset(t);
    out << "PushValues target_reg: " << t << " n: " << n;
  }
}

