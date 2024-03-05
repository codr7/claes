#ifndef CLAES_REGISTER_HPP
#define CLAES_REGISTER_HPP

#include "claes/error.hpp"

namespace claes {
  using namespace std;

  struct Register {
    int frame_offset, index;
    Register(int index): frame_offset(0), index(index) {}
  };

  inline bool operator ==(const Register &left, const Register &right) {
    return left.frame_offset == right.frame_offset && left.index == right.index;
  }

  inline ostream &operator <<(ostream &out, const Register &value) {
    out << "(Register " << 
      value.frame_offset << ':' <<  
      value.index << ')';

    return out;
  }
}

#endif
