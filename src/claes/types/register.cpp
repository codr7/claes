#include "claes/cell.hpp"
#include "claes/types/register.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  void Register::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  bool Register::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
