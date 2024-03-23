#include <cerrno>
#include <fstream>
#include <iostream>

#include "claes/form.hpp"
#include "claes/ops/goto.hpp"
#include "claes/ops/set_path.hpp"
#include "claes/ops/exit.hpp"
#include "claes/ops/loc.hpp"
#include "claes/ops/todo.hpp"
#include "claes/ops/stop.hpp"
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
    
    emit<ops::Exit>();
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

  E VM::step(Stack &stack) {
    for (auto pc = this->pc; pc < ops.size(); pc++) {
      auto const &op = ops[pc];

      switch (op.op_code()) {
      case Op::Code::LOC: {
	auto &next_op = ops[pc+1];
	auto prev_imp = next_op.imp;
	next_op.imp = make_shared<ops::Stop>(op.as<ops::Loc>().loc);
	auto e = eval(this->pc, stack);
	next_op.imp = prev_imp;
	return e;
      }
      case Op::Code::EXIT:
      case Op::Code::STOP:
	return eval(this->pc, stack);
      default:
	break;
      }
    }

    return nullopt;
  }

  void VM::stop(Stack &stack) {
    cout << "Stopped";

    if (loc) {
      cout << " in " << *loc;
    }

    cout << endl;

    for (auto c = call; c; c = c->parent) {
      cout << *c << endl;
    }

    cout << endl << stack << endl;

    if (pc < ops.size()) {
      cout << endl << pc << ' ';
      ops[pc].trace(cout);
      cout << endl;
    }

    cout << "d> ";
    string line;
    
    if (!getline(cin, line)) { 
      return; 
    }
    
    if (line == "") {
      stop(stack);
    } else if (line == "s") {
      step(stack);
    } else if (line == "q") {
      return;
    }
  }
}

