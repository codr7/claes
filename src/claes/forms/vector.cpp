#include "claes/forms/vector.hpp"
#include "claes/ops/make_vector.hpp"
#include "claes/ops/push_item.hpp"
#include "claes/vm.hpp"

namespace claes::forms {
  E Vector::emit(VM &vm, Env &env, Forms &arguments) const {
    vm.emit<ops::MakeVector>();
    
    for (const auto &it: items.items) {
      if (auto e = it.emit(vm, env, arguments); e) {
	return e;
      }

      vm.emit<ops::PushItem>();
    }

    return nullopt;
  }
}
