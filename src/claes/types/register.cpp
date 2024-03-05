#include "claes/cell.hpp"
#include "claes/ops/get_register.hpp"
#include "claes/types/register.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  void Register::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  E Register::emit_id(const Cell &value,
		      VM &vm, 
		      Env &env, 
		      Forms &args,
		      const Loc &loc) const {
    vm.emit<ops::GetRegister>(value.as(get()));
    return nullopt;
  }

  bool Register::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
