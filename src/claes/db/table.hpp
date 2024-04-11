#pragma once

#include "claes/db/definition.hpp"

namespace claes::db {
  struct TableColumn;
  
  struct Table: Definition {
    vector<TableColumn *> columns;
    Table(const string &name): Definition(name) {}
  };
}
