#ifndef CLAES_ENV_HPP
#define CLAES_ENV_HPP

#include <iostream>

#include <set>
#include <map>
#include <string>

#include "claes/cell.hpp"
#include "claes/macro.hpp"
#include "claes/method.hpp"
#include "claes/types/reg.hpp"

namespace claes {
  using namespace std;

  struct Macro;

  struct Env {
    struct Imp {
      Imp *parent;
      map<string, Cell> bindings;
      int ref_count = 1;

      Imp(Imp *parent, const set<string> &used_ids);

      void bind(const string &name, const Cell &value) {
	if (auto found = bindings.find(name); found != bindings.end()) {
	  bindings.erase(found);
	}

	bindings.insert(make_pair(name, value));
      }

      void deref() {
	if (--ref_count == 0) {
	  delete this;
	}
      }

      optional<pair<Cell, int>> find_env(const string &name, int depth = 1) const {
	if (auto found = bindings.find(name); found != bindings.end()) {
	  return make_pair(found->second, depth);
	}

	return parent ? parent->find_env(name, depth+1) : nullopt;
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

      size_t len() const {
	auto result = bindings.size();

	if (parent) {
	  result += parent->len();
	}

	return result;
      }
    };

    Imp *imp = nullptr;

    Env(Imp *parent = nullptr, const set<string> &used_ids = {}): 
      imp(new Imp(parent, used_ids)) {}

    Env(const Env &env): imp(env.imp) {
      imp->ref_count++;
    }

    ~Env() {
      imp->deref();
    }

    const Env &operator=(const Env &env) {
      imp->deref();
      imp = env.imp;
      imp->ref_count++;
      return *this;
    }

    Cell bind(const string &name, const Cell &value) {
      imp->bind(name, value);
      return value;
    }

    template <typename T, typename V>
    Cell bind(const string &name, const TType<T> &type, const V &value) {
      return bind(name, Cell(type, value));
    }

    Cell bind_macro(const string &name, int arity, const Macro::Body &body);

    Cell bind_method(const string &name,
		       const Method::Args &args,
		       const Method::Body &body);
    
    Cell bind_type(Type type);

    optional<Cell> find(const string &name) const {
      return imp->find(name);
    }

    void import_from(const Env &source) {
      imp->import_from(*source.imp);
    }
    
    size_t len() const {
      return imp->len();
    }
  };
}

#endif
