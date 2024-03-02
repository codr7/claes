#ifndef CLAES_FORMS_LITERAL_HPP
#define CLAES_FORMS_LITERAL_HPP

namespace claes::forms {
  struct Literal: Form::Imp {
    Cell value;
    
    Literal(const Location &location, const Cell &value): 
      Form::Imp(location), value(value) {}
  };
}

#endif
