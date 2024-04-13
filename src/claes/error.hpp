#ifndef CLAES_ERROR_H
#define CLAES_ERROR_H

#include <memory>
#include <optional>

#include "claes/loc.hpp"
#include "claes/utilities.hpp"

namespace claes {
  using namespace std;

  struct Error {
    struct Imp {
      Loc loc;
      string message;

      Imp(const Loc &loc, const string &message):
	loc(loc), message(message) {}
    };

    shared_ptr<const Imp> imp;

    template <typename...Args>
    Error(const Loc &loc, Args &&...args):
      imp(make_shared<const Imp>(loc, to_string(std::forward<Args>(args)...))) {}
  };

  using E = optional<Error>;

  inline ostream &operator <<(ostream &out, Error e) {
    out << "Error in " << e.imp->loc << ':' << endl << e.imp->message;
    return out;
  }
}

#endif
