#ifndef CLAES_FRAME_HPP
#define CLAES_FRAME_HPP

#include <vector>
#include "claes/cell.hpp"
#include "claes/reg.hpp"

namespace claes {
  struct Frame {
    vector<optional<Cell>> regs;

    Reg push_reg(const optional<Cell> value = nullopt) {
      Reg result(regs.size());
      regs.push_back(value);
      return result;
    }
  };
}

#endif
