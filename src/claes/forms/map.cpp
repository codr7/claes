#include "claes/forms/map.hpp"
#include "claes/ops/make_map.hpp"
#include "claes/ops/push_map_item.hpp"
#include "claes/types/map.hpp"
#include "claes/vm.hpp"

namespace claes::forms {
  E Map::emit(VM &vm, Env &env, Forms &arguments) const {
    vm.emit<ops::MakeMap>();
    
    for (const auto &it: items) {
      if (auto e = it.emit(vm, env, arguments); e) {
	return e;
      }

      vm.emit<ops::PushMapItem>();
    }

    return nullopt;
  }

  E Map::quote(VM &vm, Env &env, int depth) const {
    vm.emit<ops::MakeMap>();
    types::Map::Value result;

    for (const auto &it: items) {
      if (const auto e = it.quote(vm, env, depth); e) {
	return e;
      }
      
      vm.emit<ops::PushMapItem>();
    }

    return nullopt;
  }
}
