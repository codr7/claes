#ifndef CLAES_TYPE_HPP
#define CLAES_TYPE_HPP

#include <string>

namespace claes {
  using namespace std;

  struct Type {
    struct Imp {
      string name;
      Imp(const string &name): name(name) {}
    };

    shared_ptr<const Imp> imp;
    Type(const string &name): imp(make_shared<const Imp>(name)) {}
  };

  template <typename T> 
  struct TType: Type {
    TType(const string &name): Type(name) {}
  };
}

#endif
