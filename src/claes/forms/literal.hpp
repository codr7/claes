#ifndef CLAES_FORMS_LITERAL_HPP
#define CLAES_FORMS_LITERAL_HPP

namespace claes::forms {
  struct Literal: Form {
    struct Imp: Form::Imp {
      Imp(const Location &location, const Cell &value): Form::Imp(location), value(value) {}
      Cell value;
    };

    Literal(const Location &location, const Cell &value): 
      Form(make_shared<Imp>(location, value)) {}
  };
}

#endif
