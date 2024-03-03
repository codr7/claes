#ifndef CLAES_VM_HPP
#define CLAES_VM_HPP

#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes {
  struct Error;
  struct Stack;

  struct VM {
    PC pc = 0;
    vector<Op> ops;

    template <typename T, typename...Args>
    PC emit(Args&&...args) {
      PC result = ops.size();
      ops.emplace_back(make_shared<T>(std::forward<Args>(args)...));
      return result;
    }

    PC emit_pc() const {
      return ops.size();
    }

    optional<Error> eval(const PC start_pc, Stack &stack);
  
    void repl(istream &in, ostream &out);
  };
}

#endif
