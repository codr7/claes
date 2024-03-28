#include <curl/curl.h>

#include "claes/libs/curl.hpp"
#include "claes/types/curl.hpp"

namespace claes::libs {
  Curl::Curl(): Env() {
    bind_type(types::Curl::get());
  }
}
