#ifndef CLAES_VM_HPP
#define CLAES_VM_HPP

#include <filesystem>
#include <iostream>

#include "claes/alloc.hpp"
#include "claes/call.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"
#include "claes/reg.hpp"
#include "claes/ops/trace.hpp"

namespace claes {
  namespace fs = filesystem;

  struct Error;
  struct Form;
  struct Reg;
  struct Stack;

  static const int VERSION = 4;

  struct VM {
    Call *call = nullptr;
    Alloc<Call, 64> call_alloc;
    vector<size_t> frames;
    vector<Op> ops;
    fs::path path;
    PC pc = 0;
    int recursion_depth = 0;
    vector<Cell> regs;  
    bool trace = false;

    VM() {
      begin_frame();
    }
    
    void begin_call(const Cell &target, bool recursive, const Loc &loc) {
      begin_frame();

      if (recursive) {
	recursion_depth++;
      }

      call = call_alloc.get(call, target, recursive, loc, pc);
    }

    void begin_frame() {
      frames.push_back(regs.size());
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
      for (auto i = 0; i < regs.size() - frames.back(); i++) {
	regs.pop_back();
      }
      
      frames.pop_back();
    }

    E eval(const PC start_pc, Stack &stack);
    E eval(const Form &form, Env &env, Stack &stack);
    pair<optional<Cell>, E> eval(const Form &form, Env &env);

    int frame_offset(const Reg &reg) const {
      auto o = reg.frame_offset;
      if (o) { o += recursion_depth; }
      return o;
    }

    const Cell &get_reg(const Reg &reg) const {
      const auto &f = *next(frames.rbegin(), frame_offset(reg));
      return regs[f + reg.index];
    }

    Cell &get_reg(const Reg &reg) {
      auto &f = *next(frames.rbegin(), frame_offset(reg));
      return regs[f + reg.index];
    }
  
    E load(fs::path path, Env &env, const Loc &loc);

    void repl(istream &in, ostream &out);

    Reg push_reg(const Cell &value) {
      Reg result(regs.size());
      regs.push_back(value);
      return result;
    }

    void set_reg(const Reg &reg, const Cell &value) {
      auto &f = *next(frames.rbegin(), frame_offset(reg));
      regs[f + reg.index] = value;
    }

    E tco(const Cell &target, 
	  const PC target_pc, 
	  const PC start_pc = 0, 
	  Op *last_call = nullptr);
  };
}

#endif
