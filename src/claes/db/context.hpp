#pragma once

#ifdef USE_SQLITE

#include <cassert>
#include <iostream>

#include "claes/db/error.hpp"
#include <sqlite3.h>

namespace claes::db {
  using namespace std;
  
  struct Context {
    struct Imp {
      sqlite3 *db = nullptr;
      int ref_count = 1;

      Imp(sqlite3 *db): db(db) {}

      virtual ~Imp() {
	const auto result = sqlite3_close(db);
	assert(result == SQLITE_OK);
      }

      void deref() {
	if (--ref_count == 0) {
	  delete this;
	}
      }
    };

    Imp *imp = nullptr;

    Context(sqlite3 *db): imp(new Imp(db)) {}
    
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

    E exec(const string &sql) {
      char *e;

      sqlite3_exec(imp->db, sql.c_str(), nullptr, nullptr, &e);

      if (e) {
	const auto s = string(e);
	sqlite3_free(e);
	return E(s);
      }

      return nullopt;
    }
  };

  inline bool operator==(const Context &left, const Context &right) {
    return left.imp == right.imp;
  }

  inline strong_ordering operator<=>(const Context &left, const Context &right) {
    return left.imp <=> right.imp;
  }

  inline ostream &operator<<(ostream &out, const Context &c) {
    out << "(Context " << c.imp << ')';
    return out;
  }
  
  inline pair<optional<Context>, E> connect(const string &path) {
    sqlite3 *db = nullptr;

    if (int result = sqlite3_open(path.c_str(), &db); result != SQLITE_OK) {
      return make_pair(nullopt, Error("Failed connecting to database: ", path));
    }

    return make_pair(Context(db), nullopt);
  }
}

#endif
