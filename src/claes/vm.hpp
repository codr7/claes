#ifndef CLAES_VM_HPP
#define CLAES_VM_HPP

#include "claes/common.hpp"
#include "claes/op.hpp"
#include "claes/ops/trace.hpp"

namespace claes {
  struct Error;
  struct Stack;

  struct VM {
    bool trace = false;
    PC pc = 0;
    vector<Op> ops;

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

    E eval(const PC start_pc, Stack &stack);
  
    void repl(istream &in, ostream &out);
  };
}

#endif
