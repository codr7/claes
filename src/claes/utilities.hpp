#ifndef CLAES_UTILITIES_HPP
#define CLAES_UTILITIES_HPP

#include <sstream>

namespace claes {
  template <typename Arg, typename...Args>
  string to_string(Arg &&arg, Args &&...args) {
    stringstream buf;
    buf << arg;
    ((buf << std::forward<Args>(args)), ...);
    return buf.str();
  }
}

#endif
