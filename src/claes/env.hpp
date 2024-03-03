#ifndef CLAES_ENV_HPP
#define CLAES_ENV_HPP

#include <map>
#include <string>

#include "claes/cell.hpp"

namespace claes {
  using namespace std;

  struct Env {
    map<string, Cell> bindings;
    
    void bind(const string &name, const Cell &value) {
      if (auto found = bindings.find(name); found != bindings.end()) {
	bindings.erase(found);
      }

      bindings.insert(make_pair(name, value));
    }

    optional<Cell> find(const string &name) const {
      if (auto found = bindings.find(name); found != bindings.end()) {
	return found->second;
      }

      return nullopt;
    }
  };
}

#endif
