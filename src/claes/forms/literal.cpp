#include "claes/forms/literal.hpp"
#include "claes/types/sym.hpp"
#include "claes/vm.hpp"

namespace claes::forms {
  Cell Literal::quote(VM &vm, int depth) const {
    return value; 
  }
}
