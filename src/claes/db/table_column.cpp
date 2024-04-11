#include "claes/db/table.hpp"
#include "claes/db/table_column.hpp"

namespace claes::db {
  TableColumn::TableColumn(Table &table, const string &name):
    TableDefinition(table, name) {
    table.columns.push_back(this);
  }
}
