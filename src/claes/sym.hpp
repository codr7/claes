#ifndef CLAES_SYM_HPP
#define CLAES_SYM_HPP

#include <string>

namespace claes {
  using namespace std;
  
  struct Sym {
    string name;
    Sym(const string &name): name(name) {}
  };

  inline bool operator==(const Sym &left, const Sym &right) {
    return &left == &right;
  }
  
  inline strong_ordering operator<=>(const Sym &left, const Sym &right) {
    return left.name <=> right.name;
  }

  inline ostream &operator<<(ostream &out, const Sym &s) {
    out << '\'' << s.name;
    return out;
  }
}

#endif
