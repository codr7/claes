#include "claes/error.hpp"

namespace claes {
  struct Cell;
}

namespace claes::js {
  using P = pair<optional<Cell>, E>;

  P parse(istream &in, Loc &loc);
}
