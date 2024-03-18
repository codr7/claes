#ifndef CLAES_VM_HPP
#define CLAES_VM_HPP

#include <filesystem>
#include <iostream>

#include "claes/alloc.hpp"
#include "claes/call.hpp"
#include "claes/common.hpp"
#include "claes/frame.hpp"
#include "claes/op.hpp"
#include "claes/reg.hpp"
#include "claes/ops/trace.hpp"

namespace claes {
  struct Error;
  struct Form;
  struct Reg;
  struct Stack;

  static const int VERSION = 2;
  namespace fs = filesystem;

  struct VM {
    vector<Frame> frames;
    Alloc<Call, 64> call_alloc;
    Call *call = nullptr;
    fs::path path;
    vector<Op> ops;
    PC pc = 0;
    bool trace = false;

    VM() {
      begin_frame();
    }
    
    void begin_call(const Cell &target, const Loc &loc) {
      begin_frame();
      call = call_alloc.get(call, target, loc, pc);
    }

    void begin_frame() {
      frames.emplace_back();
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
      auto result = call;
      call = call->parent;
      end_frame();
      return result;
    }

    void end_frame() {
      frames.pop_back();
    }

    E eval(const PC start_pc, Stack &stack);
    E eval(const Form &form, Env &env, Stack &stack);
    pair<optional<Cell>, E> eval(const Form &form, Env &env);

    const Cell &get_reg(const Reg &reg) const {
      const auto &f = *next(frames.rbegin(), reg.frame_offset);
      return f.regs[reg.index];
    }

    Cell &get_reg(const Reg &reg) {
      auto &f = *next(frames.rbegin(), reg.frame_offset);
      return f.regs[reg.index];
    }
  
    E load(fs::path path, Env &env, const Loc &loc);

    void repl(istream &in, ostream &out);

    Reg push_reg(const Cell &value) {
      return frames.back().push_reg(value);
    }

    void set_reg(const Reg &reg, const Cell &value) {
      auto &f = *next(frames.rbegin(), reg.frame_offset);
      f.regs[reg.index] = value;
    }
  };
}

#endif
