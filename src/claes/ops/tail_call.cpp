#include "claes/ops/tail_call.hpp"
#include "claes/vm.hpp"

namespace claes::ops {
  void TailCall::trace(VM &vm, ostream &out) const {
    out << "TailCall reg_count: " << reg_count << " start: ";
    vm.ops[start_pc].trace(vm, out);
  }
}
