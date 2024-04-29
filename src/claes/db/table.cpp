#include "claes/db/schema.hpp"
#include "claes/db/table.hpp"

namespace claes::db {
  Table::Table(Schema &schema, const string &name): Definition(name) {
    schema.definitions.push_back(this);
  }
}
