#ifndef CLAES_LIBRARIES_CORE_HPP
#define CLAES_LIBRARIES_CORE_HPP

#include "claes/env.hpp"
#include "claes/forms/id.hpp"
#include "claes/forms/vector.hpp"
#include "claes/ops/begin_frame.hpp"
#include "claes/ops/end_frame.hpp"
#include "claes/ops/push.hpp"
#include "claes/ops/push_register.hpp"
#include "claes/types/bit.hpp"
#include "claes/types/i64.hpp"
#include "claes/types/meta.hpp"
#include "claes/types/macro.hpp"
#include "claes/types/register.hpp"
#include "claes/types/string.hpp"
#include "claes/types/vector.hpp"
#include "claes/vm.hpp"

namespace claes::libraries {
  struct Core: Env {
    Core(): Env() {
      bind_type(types::Bit::get());
      bind_type(types::I64::get());
      bind_type(types::Meta::get());
      bind_type(types::Macro::get());
      bind_type(types::Register::get());
      bind_type(types::String::get());
      bind_type(types::Vector::get());

      bind_macro("let", 
		 [](Macro self, 
		    VM &vm, 
		    Env &env, 
		    const Forms &arguments, 
		    const Loc &loc) -> E {
		   Forms args(arguments);
		   const auto &binding_forms = args.pop().as<forms::Vector>().items;
		   vm.emit<ops::BeginFrame>();
		   auto i = 0;

		   for (auto bf = binding_forms.items.begin(); 
			bf != binding_forms.items.end(); 
			bf++) {
		     const auto &name_form = *bf;
		     bf++;
		     const auto &value_form = *bf;

		     env.bind(name_form.as<forms::Id>().name, 
			      Cell(types::Register::get(), i));

		     Forms value_args;

		     if (auto e = value_form.emit(vm, env, value_args); e) {
		       return e;
		     }

		     vm.emit<ops::PushRegister>();
		   }
 
		   vm.emit<ops::EndFrame>();
		   return nullopt;
      });

      bind_macro("trace", 
		 [](Macro self, 
		    VM &vm, 
		    Env &env, 
		    const Forms &arguments, 
		    const Loc &loc) {
	vm.trace = !vm.trace;
	vm.emit<ops::Push>(Cell(types::Bit::get(), vm.trace));
	return nullopt;
      });
    }
  };

  static Core core;
}

#endif
