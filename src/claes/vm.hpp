#ifndef CLAES_VM_HPP
#define CLAES_VM_HPP

#include <filesystem>
#include <iostream>
#include <map>

#include "claes/alloc.hpp"
#include "claes/call.hpp"
#include "claes/common.hpp"
#include "claes/libs/core.hpp"
#include "claes/libs/db.hpp"
#include "claes/libs/curl.hpp"
#include "claes/op.hpp"
#include "claes/reg.hpp"
#include "claes/ops/trace.hpp"
#include "claes/sym.hpp"

namespace claes {
  namespace fs = filesystem;

  struct Error;
  struct Form;
  struct Reg;
  struct Stack;

  static const int VERSION = 8;

  struct VM {
    struct Frame {
      bool recursive;
      size_t reg_count;
      
      Frame(const size_t reg_count, bool recursive):
	recursive(recursive), reg_count(reg_count) {}
    };
    
    libs::Core core;
    libs::DB db;
    libs::Curl curl;

    bool debug = false, trace = false;

    int arity = 0;
    Call *call = nullptr;
    Alloc<Call, 64> call_alloc;
    vector<Frame> frames;
    optional<Loc> loc;
    vector<Op> ops;
    fs::path path;
    PC pc = 0;
    int recursion_depth = 0;
    vector<Cell> regs;  
    Alloc<Sym, 64> sym_alloc;
    map<string, Sym *> syms;
    
    VM() {
      begin_frame(false);
    }
    
    void begin_call(const Cell &target, bool recursive, const Loc &loc) {
      begin_frame(recursive);

      if (recursive) {
	recursion_depth++;
      }

      call = call_alloc.get(call, target, recursive, loc, pc);
    }

    void begin_frame(bool recursive) {
      frames.emplace_back(regs.size(), recursive);
    }

    template <typename T, typename...Args>
    PC emit_no_trace(Args&&...args) {      
      PC result = ops.size();
      ops.emplace_back(make_shared<T>(std::forward<Args>(args)...));
      return result;
    }

    template <typename T, typename...Args>
    PC emit(Args&&...args) {
      if (trace) {
	emit_no_trace<ops::Trace>();
      }

      return emit_no_trace<T>(std::forward<Args>(args)...);
    }

    PC emit_pc() const {
      return ops.size();
    }

    Call *end_call() {
      if (call->recursive) {
	recursion_depth--;
      }

      auto result = call;
      call = call->parent;
      end_frame();
      return result;
    }

    void end_frame() {
      for (auto i = 0; i < regs.size() - frames.back().reg_count; i++) {
	regs.pop_back();
      }
      
      frames.pop_back();
    }

    E eval(const PC start_pc, Stack &stack);
    E eval(const Form &form, Env &env, Stack &stack);
    pair<optional<Cell>, E> eval(const Form &form, Env &env);

    int frame_offset(const Reg &reg) const {
      auto o = reg.frame_offset;
      if (o && frames.back().recursive) { o += recursion_depth; }
      return o;
    }

    const Cell &get_reg(const Reg &reg) const {
      const auto &f = *next(frames.rbegin(), frame_offset(reg));
      return regs[f.reg_count + reg.index];
    }

    Cell &get_reg(const Reg &reg) {
      const auto &f = *next(frames.rbegin(), frame_offset(reg));
      return regs[f.reg_count + reg.index];
    }
  
    E load(fs::path path, Env &env, const Loc &loc);

    void repl(istream &in, ostream &out, Env &env);

    Reg push_reg(const Cell &value) {
      Reg result(regs.size());
      regs.push_back(value);
      return result;
    }

    void set_reg(const Reg &reg, const Cell &value) {
      auto &f = *next(frames.rbegin(), frame_offset(reg));
      regs[f.reg_count + reg.index] = value;
    }

    E single_step(Stack &stack);

    E step(Stack &stack);

    E stop(Stack &stack);

    const Sym *sym(const string &name) {
      if (const auto found = syms.find(name); found != syms.end()) {
	return found->second;
      }

      const auto s = sym_alloc.get(name);
      syms.insert(make_pair(name, s));
      return s; 
    }
    
    
    E tco(const Cell &target, 
	  const PC target_pc, 
	  const PC start_pc = 0, 
	  Op *last_call = nullptr);
  };
}

#endif
