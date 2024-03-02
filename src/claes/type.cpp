#include "claes/cell.hpp"
#include "claes/type.hpp"

namespace claes {
  Cell Type::Imp::clone(const Cell &value) const {
    return value;
  }

  Cell Type::clone(const Cell &value) const {
    return imp->clone(value);
  }
}
