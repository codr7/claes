#ifndef CLAES_FRAME_HPP
#define CLAES_FRAME_HPP

#include <vector>
#include "claes/cell.hpp"

namespace claes {
  struct Frame {
    vector<Cell> regs;
  };
}

#endif
