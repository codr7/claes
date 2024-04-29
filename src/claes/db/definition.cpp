#include "claes/db/context.hpp"
#include "claes/db/definition.hpp"

namespace claes::db {
  E Definition::create(Context &context) const {
    return context.exec(create_sql());
  }

  E Definition::drop(Context &context) const {
    return context.exec(drop_sql());
  }
}
