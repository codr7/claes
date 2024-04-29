#pragma once

#include <ostream>
#include <vector>

namespace claes::db {
  using namespace std;
  struct Definition;
  
  struct Schema {
    vector<Definition *> definitions;
  };

  inline bool operator==(const Schema &left, const Schema &right) {
    return &left == &right;
  }

  inline strong_ordering operator<=>(const Schema &left, const Schema &right) {
    return &left <=> &right;
  }

  inline ostream &operator<<(ostream &out, const Schema &s) {
    out << "(Schema)";
    return out;
  }
}
