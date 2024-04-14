#include "claes/libs/db.hpp"
#include "claes/db/context.hpp"
#include "claes/db/types/context.hpp"
#include "claes/types/string.hpp"

namespace claes::libs {
  DB::DB(): Env() {
#ifdef USE_SQLITE
    bind_type(db::types::Context::get());

    bind_method("connect", {"path"},
		[](const Method &self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const Loc &loc) -> E {
		  const auto p = stack.pop().as(types::String::get());
		  auto [cx, e] = db::connect(p);

		  if (e) {
		    return Error(loc, e->imp->message);
		  }

		  stack.push(db::types::Context::get(), *cx);
		  return nullopt;
		});
#endif
  }
}

