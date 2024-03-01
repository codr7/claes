#ifndef CLAES_FORMS_ID_HPP
#define CLAES_FORMS_ID_HPP

namespace claes::forms {
  struct Id: Form {
    struct Imp: Form::Imp {
      Imp(const Location &location, string &name): Form::Imp(location), name(name) {}
      Cell value;
    };

    Id(const Location &location, const string &name): 
      Form(make_shared<Imp>(location, name)) {}
  };
}

#endif
