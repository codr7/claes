#pragma once

#include <map>
#include "claes/cell.hpp"

namespace claes {
  using Map = map<Cell, Cell>;

  bool push(Map &map, const Cell &item);
}
