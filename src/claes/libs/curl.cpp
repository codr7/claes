#include <curl/curl.h>

#include "claes/libs/curl.hpp"
#include "claes/types/curl.hpp"

namespace claes::libs {
  Curl::Curl(): Env() {
    bind_type(types::Curl::get());

    bind_method("curl", {"url"},
		[](const Method &self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const Loc &loc) -> E {
		  return claes::Curl().call(vm, stack, arity, loc);
		});
  }
}
