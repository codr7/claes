#ifdef USE_SQLITE

#include "claes/cell.hpp"
#include "claes/db/types/context.hpp"

namespace claes::db::types {
  void Context::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  bool Context::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}

#endif
