#ifndef CLAES_LIBS_CORE_HPP
#define CLAES_LIBS_CORE_HPP

#include <iostream>

#include "claes/env.hpp"

namespace claes::libs {
  struct Core: Env {
    Core();
  };

  static Core core;
}

#endif
