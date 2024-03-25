#include "claes/forms/literal.hpp"
#include "claes/types/sym.hpp"
#include "claes/vm.hpp"

namespace claes::forms {
  pair<optional<Cell>, E> Literal::quote(VM &vm, int depth) const {
    return make_pair(value, nullopt); 
  }
}
