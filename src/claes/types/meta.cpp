#include "claes/cell.hpp"
#include "claes/types/meta.hpp"

namespace claes::types {
  void Meta::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  bool Meta::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
