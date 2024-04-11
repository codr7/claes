#pragma once

#include <string>

namespace claes::db {
  using namespace std;
  
  struct Definition {
    string name;
    Definition(const string &name): name(name) {}
  };
}
