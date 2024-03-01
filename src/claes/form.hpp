#ifndef CLAES_FORM_HPP
#define CLAES_FORM_HPP

namespace claes {
  struct Form {
    struct Imp {
      Location location;
      Imp(const Location &location): location(location) {}
    };

    shared_ptr<Imp> imp;
    Form(shared_ptr<const Imp> imp);
  };
}

#endif
