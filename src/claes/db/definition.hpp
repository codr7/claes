#pragma once

#include <string>
#include "claes/db/error.hpp"

namespace claes::db {
  using namespace std;

  struct Context;
  
  struct Definition {
    string name;
    Definition(const string &name): name(name) {}

    virtual E create(Context &context) const;

    virtual string create_sql() const {
      return to_string("CREATE ", definition_type(), " IF NOT EXISTS ", name); 
    }

    virtual string definition_type() const = 0;
    virtual E drop(Context &context) const;

    virtual string drop_sql() const {
      return to_string("DROP ", definition_type(), " IF EXISTS ", name); 
    }
  };
}
