#ifdef USE_SQLITE

#include <iostream>
#include "claes/cell.hpp"
#include "claes/forms.hpp"
#include "claes/db/types/schema.hpp"

namespace claes::db::types {
  void Schema::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  claes::E Schema::emit_call(const Cell &value,
		    VM &vm, 
		    Env &env, 
		    const Forms &args,
		    const claes::Loc &loc) const {
    cout << "schema emit " << args << endl;
    return nullopt;
  }

  bool Schema::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}

#endif
