#ifdef USE_CONTEXT

#include "claes/cell.hpp"
#include "claes/types/context.hpp"
#include "claes/types/string.hpp"
#include "claes/stack.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  void Context::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  bool Context::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}

#endif
