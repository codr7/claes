#ifndef CLAES_OP_HPP
#define CLAES_OP_HPP

#include <ostream>
#include <memory>

namespace claes {
  using namespace std;

  struct Op {
    enum struct Code {BEGIN_FRAME, BENCHMARK, BRANCH, 
		      CALL_DIRECT, CALL_INDIRECT, CALL_REG, CHECK,
		      DECREMENT, DEREF,
		      END_FRAME, EQZ, EXIT,
		      FOR,
		      GET_REG, GOTO,
		      ITER,
		      LOC,
		      MAKE_PAIR, MAKE_REF, MAKE_VECTOR,
		      PUSH, PUSH_REGS, PUSH_VALUES, PUSH_VECTOR_ITEM,
		      RECALL, RETURN,
		      SET_PATH, SET_REF, SET_REF_DIRECT, SET_REG, SPLAT, STOP, 
		      TAIL_CALL, TODO, TRACE};

    struct Imp {
      Code code;
      Imp(Code code): code(code) {}
      virtual ~Imp() {}
      virtual void trace(ostream &out) const = 0;
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

    void trace(ostream &out) const {
      return imp->trace(out);
    }
  };
}

#endif
