#ifndef CLAES_LIBS_CURL_HPP
#define CLAES_LIBS_CURL_HPP

#include <iostream>

#include "claes/env.hpp"

namespace claes::libs {
  struct Curl: Env {
    Curl();
  };

  static Curl curl;
}

#endif
