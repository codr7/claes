#ifndef CLAES_TYPE_HPP
#define CLAES_TYPE_HPP

#include <string>

namespace claes {
  using namespace std;

  struct Type {
    struct Imp {
      string name;
      Imp(string name): name(std::move(name)) {}
    };

    shared_ptr<const Imp> imp;
    Type(string name): imp(make_shared<const Imp>(std::move(name))) {}
  };

  template <typename T> 
  struct TType: Type {
    TType(string name): Type(std::move(name)) {}
  };
}

#endif
