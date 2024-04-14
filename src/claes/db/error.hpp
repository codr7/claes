#pragma once

#include "claes/utilities.hpp"

namespace claes::db {
  using namespace std;

  struct Error {
    struct Imp {
      string message;
      Imp(const string &message): message(message) {}
    };

    shared_ptr<const Imp> imp;

    template <typename...Args>
    Error(Args &&...args):
      imp(make_shared<const Imp>(to_string(std::forward<Args>(args)...))) {}
  };

  using E = optional<Error>;

  inline ostream &operator <<(ostream &out, Error e) {
    out << e.imp->message;
    return out;
  }
}
