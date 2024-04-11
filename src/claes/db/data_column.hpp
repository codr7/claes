#pragma once

#include "claes/table_column.hpp"

namespace claes::db {
  template <typename T>
  struct DataColumn: TableColumn {
    DataColumn(Table &table, const string &name): TableColumn(table, name) {}
  };
}
