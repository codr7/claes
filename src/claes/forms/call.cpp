#include "claes/cell.hpp"
#include "claes/forms/call.hpp"
#include "claes/types/pair.hpp"
#include "claes/types/vector.hpp"

namespace claes::forms {
  pair<optional<Cell>, E> Call::quote(VM &vm, int depth) const {
    types::Vector::Value qas;

    for (const auto &a: args) {
      const auto [v, e] = a.quote(vm, depth);

      if (e) {
	return make_pair(nullopt, e);
      }
      
      qas.push_back(*v);
    }

    const auto [v, e] = target.quote(vm, depth);

    if (e) {
      return make_pair(nullopt, e);
    }
    
    auto result = Cell(types::Pair::get(),
		       make_pair(*v, Cell(types::Vector::get(), qas)));

    return make_pair(result, nullopt);
  }
}
