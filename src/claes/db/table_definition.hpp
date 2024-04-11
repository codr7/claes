#pragma once

#include "claes/db/definition.hpp"

namespace claes::db {
  struct Table;
  
  struct TableDefinition: Definition {
    Table &table;

    TableDefinition(Table &table, const string &name):
      Definition(name), table(table) {}
  };
}
