#ifndef CLAES_VM_HPP
#define CLAES_VM_HPP

#include "claes/common.hpp"
#include "claes/frame.hpp"
#include "claes/op.hpp"
#include "claes/register.hpp"
#include "claes/ops/trace.hpp"

namespace claes {
  struct Error;
  struct Register;
  struct Stack;

  struct VM {
    vector<Frame> frames;
    vector<Op> ops;
    PC pc = 0;
    bool trace = false;

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

    void end_frame() {
      frames.pop_back();
    }

    E eval(const PC start_pc, Stack &stack);

    const Cell &get_register(const Register &reg) const {
      const auto &f = *next(frames.rbegin(), reg.frame_offset);
      return f.registers[reg.index];
    }

    Cell &get_register(const Register &reg) {
      auto &f = *next(frames.rbegin(), reg.frame_offset);
      return f.registers[reg.index];
    }
  
    void repl(istream &in, ostream &out);

    void push_register(const Cell &value) {
      frames.back().registers.push_back(value);
    }
  };
}

#endif
