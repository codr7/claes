#pragma once

#include <iostream>

#include "claes/env.hpp"

namespace claes::libs {
  struct DB: Env {
    DB();
  };

  static DB db;
}
