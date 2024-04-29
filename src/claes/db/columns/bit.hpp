#pragma once

#include "claes/db/table_column.hpp"

namespace claes::db::columns {
  struct Bit: TableColumn<bool> {
    Bit(Table &table, const string &name);

    virtual string column_type() const override {
      return "INTEGER";
    }
  };
}
