#include "claes/cell.hpp"
#include "claes/forms/call.hpp"
#include "claes/types/pair.hpp"
#include "claes/types/vector.hpp"

namespace claes::forms {
  Cell Call::quote(VM &vm, int depth) const {
    types::Vector::Value qas;

    for (const auto &a: args) {
      qas.push_back(a.quote(vm, depth));
    }
    
    return Cell(types::Pair::get(),
		make_pair(target.quote(vm, depth),
			  Cell(types::Vector::get(), qas)));
  }
}
