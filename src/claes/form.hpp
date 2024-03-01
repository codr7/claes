#ifndef CLAES_FORM_HPP
#define CLAES_FORM_HPP

namespace claes {
  struct Form {
    struct Imp {
      Location location;

      Imp(Location location): location(move(location)) {}
    };

    shared_ptr<Imp> imp;

    Form(shared_ptr<const Imp> imp);
  };
}

#endif
