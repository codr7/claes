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

  inline bool operator==(const Loc &left, const Loc &right) {
    return 
      left.source == right.source && 
      left.line == right.line && 
      left.column == right.column;
  }

  inline strong_ordering operator<=>(const Loc &left, const Loc &right) {
    if (auto r = left.source <=> right.source; r != strong_ordering::equal) {
      return r;
    }

    if (auto r = left.line <=> right.line; r != strong_ordering::equal) {
      return r;
    }

    if (auto r = left.column <=> right.column; r != strong_ordering::equal) {
      return r;
    }

    return strong_ordering::equal;
  }

  inline ostream &operator <<(ostream &out, Loc loc) {
    out << loc.source << '@' << loc.line << ':' << loc.column;
    return out;
  }
}

#endif
