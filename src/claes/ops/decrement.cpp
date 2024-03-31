#include "claes/ops/decrement.hpp"
#include "claes/vm.hpp"

namespace claes::ops {
  void Decrement::trace(VM &vm, ostream &out) const {
    Reg t = target_reg;
    t.frame_offset = vm.frame_offset(t);
    out << "Decrement target_reg: " << t;
  }
}
