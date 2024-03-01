#ifndef CLAES_LOCATION_HPP
#define CLAES_LOCATION_HPP

#include <string>
#include <ostream>

namespace claes {
  using namespace std;
  
  struct Location {
    static const Location INVALID;
    
    Location(const string &source = "?", int line = -1, int column = -1):
      source(source), line(line), column(column) {}

    string source;
    int line, column;
  };

  ostream &operator <<(ostream &out, Location location);
}

#endif
