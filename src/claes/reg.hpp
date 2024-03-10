#ifndef CLAES_REG_HPP
#define CLAES_REG_HPP

#include "claes/error.hpp"

namespace claes {
  using namespace std;

  struct Reg {
    int frame_offset, index;
    Reg(int index): frame_offset(0), index(index) {}
  };

  inline bool operator==(const Reg &left, const Reg &right) {
    return left.frame_offset == right.frame_offset && left.index == right.index;
  }

  inline strong_ordering operator<=>(const Reg &left, const Reg &right) {
    if (left.frame_offset != right.frame_offset) {
      return left.frame_offset <=> right.frame_offset;
    }

    return left.index <=> right.index;
  }

  inline ostream &operator<<(ostream &out, const Reg &value) {
    out << "(Reg " << 
      value.frame_offset << ':' <<  
      value.index << ')';

    return out;
  }
}

#endif
