#include "claes/error.hpp"

namespace claes {
  struct Cell;
}

namespace claes::js {
  using P = pair<optional<Cell>, E>;

  P parse(istream &in, Loc &loc);

  P parse_array(istream &in, Loc &loc);
  P parse_id(istream &in, Loc &loc);
  P parse_number(istream &in, Loc &loc);
  P parse_object(istream &in, Loc &loc);
  P parse_string(istream &in, Loc &loc);
  P parse_ws(istream &in, Loc &loc);
}
