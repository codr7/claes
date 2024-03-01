#include "claes/location.hpp"

namespace claes {
  const Location Location::INVALID;

  ostream &operator <<(ostream &out, Location location) {
    out << location.source << '@' << location.line << ':' << location.column;
    return out;
  }
}
