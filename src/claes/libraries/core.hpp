#ifndef CLAES_LIBRARIES_CORE_HPP
#define CLAES_LIBRARIES_CORE_HPP

#include "claes/env.hpp"
#include "claes/ops/push.hpp"
#include "claes/types/bit.hpp"
#include "claes/types/i64.hpp"
#include "claes/types/meta.hpp"
#include "claes/types/macro.hpp"
#include "claes/types/string.hpp"
#include "claes/vm.hpp"

namespace claes::libraries {
  struct Core: Env {
    Core(): Env() {
      bind_type(types::Bit::get());
      bind_type(types::I64::get());
      bind_type(types::Meta::get());
      bind_type(types::Macro::get());
      bind_type(types::String::get());

      bind_macro("trace", 
		 [](Macro self, 
		    VM &vm, 
		    Env &env, 
		    const Forms &arguments, 
		    const Location &location) {
	vm.trace = !vm.trace;
	vm.emit<ops::Push>(Cell(types::Bit::get(), vm.trace));
	return nullopt;
      });
    }
  };

  static Core core;
}

#endif
