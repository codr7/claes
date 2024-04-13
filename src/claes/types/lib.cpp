#include "claes/cell.hpp"
#include "claes/ops/push.hpp"
#include "claes/types/lib.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  void Lib::dump(const Cell &value, ostream &out) const {
    out << "(Lib " << value.as(get()) << ')';
  }

  bool Lib::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
