#include "claes/env.hpp"
#include "claes/types/macro.hpp"
#include "claes/types/meta.hpp"
#include "claes/types/method.hpp"

namespace claes {
  Env::Imp::Imp(Imp *parent, const set<string> &used_ids): parent(parent) {
    if (parent) {
      for (const auto &id: used_ids) {
	auto found = parent->find_env(id);
	    
	if (found) {
	  auto [v, d] = *found;
	      
	  if (v.type == types::Reg::get()) {
	    auto r = v.as(types::Reg::get());
	    r.frame_offset += d;
	    bind(id, Cell(types::Reg::get(), r));
	  }
	}
      }
    }
  }

  Cell Env::bind_macro(const string &name, int arity, const Macro::Body &body) {
    return bind(name, Cell(types::Macro::get(), Macro(name, arity, body)));
  }

  Cell Env::bind_method(const string &name,
			const Method::Args &args,
			const Method::Body &body) {
    return bind(name, Cell(types::Method::get(), Method(name, args, body)));
  }

  Cell Env::bind_type(Type type) {
    return bind(type.imp->name, Cell(types::Meta::get(), type));
  }
}
