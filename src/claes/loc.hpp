#ifndef CLAES_LOC_HPP
#define CLAES_LOC_HPP

#include <string>
#include <ostream>

namespace claes {
  using namespace std;
  
  struct Loc {
    static const Loc INVALID;
    
    Loc(const string &source, int line = 1, int column = 1):
      source(source), line(line), column(column) {}

    string source;
    int line, column;
  };

  inline ostream &operator <<(ostream &out, Loc loc) {
    out << loc.source << '@' << loc.line << ':' << loc.column;
    return out;
  }
}

#endif
