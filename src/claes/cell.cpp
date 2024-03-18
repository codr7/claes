#include "claes/cell.hpp"
#include "claes/types/bit.hpp"
#include "claes/types/nil.hpp"

namespace claes {
  const Cell &NIL() {
    static Cell v(types::Nil::get(), nullptr);
    return v;
  }

  const Cell &T() {
    static Cell v(types::Bit::get(), true);
    return v;
  }
  
  const Cell &F() {
    static Cell v(types::Bit::get(), false);
    return v;
  }
}
