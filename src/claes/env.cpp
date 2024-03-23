#include "claes/env.hpp"
#include "claes/types/macro.hpp"
#include "claes/types/meta.hpp"
#include "claes/types/method.hpp"

namespace claes {
  void Env::bind_macro(const string &name, const Macro::Body &body) {
    bind(name, Cell(types::Macro::get(), Macro(name, body)));
  }

  void Env::bind_method(const string &name, int arity, const Method::Body &body) {
    bind(name, Cell(types::Method::get(), Method(name, arity, body)));
  }

  void Env::bind_type(Type type) {
    bind(type.imp->name, Cell(types::Meta::get(), type));
  }
}
