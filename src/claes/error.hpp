#ifndef CLAES_ERROR_H
#define CLAES_ERROR_H

#include "claes/location.hpp"
#include "claes/utilities.hpp"

namespace claes {
  using namespace std;

  struct Error {
    struct Imp {
      Location location;
      string message;

      Imp(const Location &location, const string &message):
	location(location), message(message) {}
    };

    shared_ptr<const Imp> imp;

    template <typename...Args>
    Error(const Location &location, Args &&...args):
      imp(make_shared<const Imp>(location, to_string(std::forward<Args>(args)...))) {}
  };

  using E = optional<Error>;

  inline ostream &operator <<(ostream &out, Error e) {
    out << "Error in " << e.imp->location << ':' << endl << e.imp->message;
    return out;
  }
}

#endif
