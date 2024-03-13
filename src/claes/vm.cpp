#include <cerrno>
#include <fstream>
#include <iostream>

#include "claes/form.hpp"
#include "claes/ops/goto.hpp"
#include "claes/ops/set_path.hpp"
#include "claes/ops/stop.hpp"
#include "claes/ops/todo.hpp"
#include "claes/read.hpp"
#include "claes/stack.hpp"
#include "claes/vm.hpp"

namespace claes {
  E VM::eval(const Form &form, Env &env, Stack &stack) {
    const auto skip_pc = emit<ops::Todo>(form.imp->loc);
    const auto start_pc = emit_pc();    
    Forms emit_args;

    if (auto e = form.emit(*this, env, emit_args); e) {
      return e;
    }
    
    emit<ops::Stop>();
    ops[skip_pc].imp = make_shared<ops::Goto>(emit_pc());
  
    if (auto e = eval(start_pc, stack); e) {
      return e;
    }

    return nullopt;
  }

  pair<optional<Cell>, E> VM::eval(const Form &form, Env &env) {
    Stack stack;

    if (auto e = eval(form, env, stack); e) {
      return make_pair(nullopt, e);
    }

    return make_pair(stack.pop(), nullopt);
  }

  E VM::load(fs::path path, Env &env, const Loc &loc) {
    const auto p = this->path / path;
    const auto prev_path = this->path;
    this->path = p.root_path() / p.relative_path().remove_filename();
    ifstream in(p);
     
    if (in.fail()) {
      return Error(loc, "Failed opening file ", p, ":\n", strerror(errno));
    }

    Loc load_loc(path, 1, 1);
    Forms fs;

    if (auto [_, e] = read_forms(in, fs, load_loc); e) {
      return e;
    }
      
    emit<ops::SetPath>(this->path);

    if (auto e = fs.emit(*this, env); e) {
      return e;
    }

    emit<ops::SetPath>(prev_path);
    this->path = prev_path;
    return nullopt;
  }
}

