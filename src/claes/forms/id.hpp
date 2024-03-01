#ifndef CLAES_FORMS_ID_HPP
#define CLAES_FORMS_ID_HPP

#include "claes/form.hpp"

namespace claes::forms {
  struct Id: Form {
    struct Imp: Form::Imp {
      Imp(const Location &location, string &name): Form::Imp(location), name(name) {}
      string name;
    };

    Id(const Location &location, const string &name): 
      Form(make_shared<Imp>(location, name)) {}
  };
}

#endif
