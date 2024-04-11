#pragma once

#include "claes/db/error.hpp"
#include <sqlite3.h>

namespace claes::db {
  struct Context {
    struct Imp {
      sqlite3 *db;
      int ref_count = 1;

      Imp(sqlite3 *db): db(db) {}

      void deref() {
	if (--ref_count == 0) {
	  delete this;
	}
      }
    };

    Imp *imp = nullptr;

    Context(sqlite3 *db): imp(db) {}

    Context(const Context &source): imp(source.imp) {
      imp->ref_count++;
    }

    ~Context() {
      imp->deref();
    }

    const Context &operator=(const Context &other) {
      imp->deref();
      imp = other.imp;
      imp->ref_count++;
      return *this;
    }
  };
  
  inline pair<Context, E> *connect(fs::path path) {
    sqlite3 *db = nullptr;

    if (int e = sqlite3_open(path, &db); e) {
      return make_pair(nullptr, Error(sqlite3_errmsg(db)));
    }

    return make_pair(Context(db), nullopt);
  }
}
