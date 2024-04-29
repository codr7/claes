#pragma once

#include <vector>
#include "claes/db/definition.hpp"

namespace claes::db {
  struct Schema;
  struct TableColumn;
  
  struct Table: Definition {
    vector<TableColumn *> columns;
    
    Table(Schema &schema, const string &name);

    virtual string definition_type() const override {
      return "TABLE";
    }
  };
}
