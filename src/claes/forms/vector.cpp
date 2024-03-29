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

  E Vector::quote(VM &vm, Env &env, int depth) const {
    vm.emit<ops::MakeVector>();
    types::Vector::Value result;

    for (const auto &it: items) {
      if (const auto e = it.quote(vm, env, depth); e) {
	return e;
      }
      
      vm.emit<ops::PushVectorItem>();
    }

    return nullopt;
  }
}
