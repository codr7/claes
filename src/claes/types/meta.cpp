#include "claes/cell.hpp"
#include "claes/ops/push.hpp"
#include "claes/types/meta.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  void Meta::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  E Meta::emit_ref(const Cell &value,
		   VM &vm, 
		   Env &env, 
		   Forms &args,
		   const Loc &loc) const {
    vm.emit<ops::Push>(value);
    return nullopt;
  }

  bool Meta::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
