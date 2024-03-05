#ifndef CLAES_ENV_HPP
#define CLAES_ENV_HPP

#include <map>
#include <string>

#include "claes/cell.hpp"
#include "claes/macro.hpp"

namespace claes {
  using namespace std;

  struct Macro;

  struct Env {
    struct Imp {
      shared_ptr<Imp> parent;
      map<string, Cell> bindings;
      
      Imp(shared_ptr<Imp> parent): parent(parent) {}

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

	return parent ? parent->find(name) : nullopt;
      }

      void import_from(const Imp &source) {
	if (source.parent) {
	  import_from(*source.parent);
	}

	for (auto b: source.bindings) {
	  bind(b.first, b.second);
	}
      }
    };

    shared_ptr<Imp> imp;

    Env(optional<Env> parent = nullopt): 
      imp(make_shared<Imp>(parent ? parent->imp : nullptr)) {}

    void bind(const string &name, const Cell &value) {
      imp->bind(name, value);
    }

    void bind_macro(const string &name, const Macro::Body &body);

    void bind_type(Type type);

    optional<Cell> find(const string &name) const {
      return imp->find(name);
    }

    void import_from(const Env &source) {
      imp->import_from(*source.imp);
    }
  };
}

#endif
