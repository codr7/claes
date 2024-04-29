#pragma once

#include "claes/db/column.hpp"
#include "claes/db/table_definition.hpp"

namespace claes::db {
  struct TableColumn: Column, TableDefinition {
    TableColumn(Table &table, const string &name);

    virtual string definition_type() const override {
      return "COLUMN";
    }

    virtual string column_type() const = 0;
  };
}
