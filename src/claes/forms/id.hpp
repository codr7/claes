#ifndef CLAES_FORMS_ID_HPP
#define CLAES_FORMS_ID_HPP

#include "claes/form.hpp"

namespace claes::forms {
  struct Id: Form::Imp {
    static Form make(const Location &location, const string &name) {
      return Form::make<Id>(location, name);
    };

    string name;
    Id(const Location &location, const string &name): Form::Imp(location), name(name) {}
  };
}

#endif
