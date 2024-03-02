#ifndef CLAES_OP_HPP
#define CLAES_OP_HPP

#include "claes/location.hpp"

namespace claes {
  struct Op {
    enum struct Code {BENCHMARK, BRANCH, PUSH, STOP};

    struct Imp {
      Code code;
      Imp(Code code): code(code) {}
    };
    
    shared_ptr<const Imp> imp;
    Op(shared_ptr<const Imp> imp = nullptr): imp(imp) {}

    template <typename T>
    const T &as() const { 
      return *static_cast<const T *>(imp.get());
    }

    template <typename T, typename...Args>
    void init(Args&&...args) {
      imp = make_shared<T>(std::forward<Args>(args)...);
    }

    Code op_code() const {
      return imp->code;
    }
  };
}

#endif
