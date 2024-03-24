#include "claes/forms/vector.hpp"
#include "claes/ops/make_vector.hpp"
#include "claes/ops/push_vector_item.hpp"
#include "claes/types/vector.hpp"
#include "claes/vm.hpp"

namespace claes::forms {
  E Vector::emit(VM &vm, Env &env, Forms &arguments) const {
    vm.emit<ops::MakeVector>();
    
    for (const auto &it: items) {
      if (auto e = it.emit(vm, env, arguments); e) {
	return e;
      }

      vm.emit<ops::PushVectorItem>();
    }

    return nullopt;
  }

  Cell Vector::quote(VM &vm, int depth) const {
    types::Vector::Value result;

    for (const auto &it: items) {
      result.push_back(it.quote(vm, depth));
    }

    return Cell(types::Vector::get(), result);
  }
}
