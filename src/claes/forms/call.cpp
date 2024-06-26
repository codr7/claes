#include "claes/cell.hpp"
#include "claes/forms/call.hpp"
#include "claes/forms/unquote.hpp"
#include "claes/ops/call_indirect.hpp"
#include "claes/ops/make_pair.hpp"
#include "claes/ops/make_vector.hpp"
#include "claes/ops/push_vector_item.hpp"
#include "claes/types/pair.hpp"
#include "claes/types/vector.hpp"
#include "claes/vm.hpp"

namespace claes::forms {
  E Call::quote(VM &vm, Env &env, int depth) const {
    if (const auto t = target.as<Unquote>(); t) {      
      for (const auto &a: args) {
	if (const auto e = a.quote(vm, env, depth); e) {
	  return e;
	}
      }
      
      Forms my_args;

      if (const auto e = t->target.emit(vm, env, my_args); e) {
	return e;
      }
      
      vm.emit<ops::CallIndirect>(args.len(), loc);
    } else {
      if (const auto e = target.quote(vm, env, depth); e) {
	return e;
      }

      vm.emit<ops::MakeVector>();
      
      for (const auto &a: args) {
	if (const auto e = a.quote(vm, env, depth); e) {
	  return e;
	}
	
	vm.emit<ops::PushVectorItem>();
      }
      
      vm.emit<ops::MakePair>();
    }
    
    return nullopt;
  }
}
