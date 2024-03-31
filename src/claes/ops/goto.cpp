#include "claes/ops/goto.hpp"
#include "claes/vm.hpp"

namespace claes::ops {
  void Goto::trace(VM &vm, ostream &out) const {
    out << "Goto: ";
    vm.ops[pc].trace(vm, out);
  }
}
