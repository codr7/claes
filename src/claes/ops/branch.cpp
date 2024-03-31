#include "claes/ops/branch.hpp"
#include "claes/vm.hpp"

namespace claes::ops {
  void Branch::trace(VM &vm, ostream &out) const {
    out << "Branch else: ";
    vm.ops[else_pc].trace(vm, out);
  }
}
