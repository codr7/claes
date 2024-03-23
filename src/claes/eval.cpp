#include <iostream>

#include "claes/error.hpp"
#include "claes/ops/benchmark.hpp"
#include "claes/ops/branch.hpp"
#include "claes/ops/call_direct.hpp"
#include "claes/ops/call_indirect.hpp"
#include "claes/ops/call_reg.hpp"
#include "claes/ops/check.hpp"
#include "claes/ops/decrement.hpp"
#include "claes/ops/deref.hpp"
#include "claes/ops/for.hpp"
#include "claes/ops/get_reg.hpp"
#include "claes/ops/goto.hpp"
#include "claes/ops/push.hpp"
#include "claes/ops/push_regs.hpp"
#include "claes/ops/push_values.hpp"
#include "claes/ops/recall.hpp"
#include "claes/ops/set_path.hpp"
#include "claes/ops/set_ref.hpp"
#include "claes/ops/set_ref_direct.hpp"
#include "claes/ops/set_reg.hpp"
#include "claes/ops/stop.hpp"
#include "claes/ops/tail_call.hpp"
#include "claes/ops/todo.hpp"
#include "claes/stack.hpp"
#include "claes/timer.hpp"
#include "claes/types/bit.hpp"
#include "claes/types/iter.hpp"
#include "claes/types/pair.hpp"
#include "claes/types/ref.hpp"
#include "claes/types/vector.hpp"
#include "claes/vm.hpp"

#define DISPATCH(next_pc)						\
  goto *dispatch[static_cast<int>((op = ops[(pc = (next_pc))]).op_code())]

namespace claes {
  using namespace std;
  
  E VM::eval(const PC start_pc, Stack &stack) {
    static const void* dispatch[] = {
      &&BEGIN_FRAME, &&BENCHMARK, &&BRANCH,
      &&CALL_DIRECT, &&CALL_INDIRECT, &&CALL_REG, &&CHECK,
      &&DECREMENT, &&DEREF, 
      &&END_FRAME, &&EQZ,
      &&FOR,
      &&GET_REG, &&GOTO,
      &&ITER,
      &&MAKE_PAIR, &&MAKE_REF, &&MAKE_VECTOR,
      &&PUSH, &&PUSH_REGS, &&PUSH_VALUES, &&PUSH_VECTOR_ITEM,
      &&RECALL, &&RETURN,
      &&SET_PATH, &&SET_REF, &&SET_REF_DIRECT, &&SET_REG, &&STOP,
      &&TAIL_CALL, &&TODO, &&TRACE};

    Op op;
    DISPATCH(start_pc);

  BEGIN_FRAME: {
      begin_frame();
    }

    DISPATCH(pc+1);

  BENCHMARK: {
      const auto n = op.as<ops::Benchmark>().repetitions;
      const auto start_pc = pc+1;

      for (auto i = 0; i < n; i++) {
	Stack s;
	if (auto e = eval(start_pc, s); e) { return e; }
      }

      Timer t;

      for (auto i = 0; i < n; i++) {
	Stack s;
	if (auto e = eval(start_pc, s); e) { return e; }
      }

      stack.push(types::I64::get(), t.ms());
    }
    
    DISPATCH(pc);
    
  BRANCH: {}
    
    DISPATCH(stack.pop().is_true() ? pc+1 : op.as<ops::Branch>().else_pc);

  CALL_DIRECT: {
      const auto &cd = op.as<ops::CallDirect>();
      pc++;
      auto t = cd.target;
      
      if (auto e = t.call(*this, stack, cd.arity, cd.loc); e) {
	return e;
      }
    }
    
    DISPATCH(pc);

  CALL_INDIRECT: {
      const auto &ci = op.as<ops::CallIndirect>();
      pc++;

      if (auto e = stack.pop().call(*this, stack, ci.arity, ci.loc); e) {
	return e;
      }
    }
    
    DISPATCH(pc);

  CALL_REG: {
      const auto &cr = op.as<ops::CallReg>();
      auto &t = get_reg(cr.target_reg);
      pc++;

      if (auto e = t.call(*this, stack, cr.arity, cr.loc); e) {
	return e;
      }
    }
    
    DISPATCH(pc);

  CHECK: {
      const auto expected = stack.pop();
      Stack s;

      if (auto e = eval(pc+1, s); e) {
	return e;
      }
      
      const auto actual = s.pop();

      if (actual != expected) {
	return Error(op.as<ops::Check>().loc, 
		     "Check failed; expected ", expected, ", actual ", actual);
      }
    }

    DISPATCH(pc);

  DECREMENT: {
      const auto &d = op.as<ops::Decrement>();
      auto &v = get_reg(d.target_reg);
      v.as(types::I64::get())--;
      stack.push(v);
    }

    DISPATCH(pc+1);

  DEREF: {
      stack.push(stack.pop().as(types::Ref::get()).imp->value);
    }
    
    DISPATCH(pc+1);

  END_FRAME: {
      end_frame();
    }
    
    DISPATCH(pc+1);

  EQZ: {
      auto &v = stack.peek();
      bool z = !v.as(types::I64::get());
      v = Cell(types::Bit::get(), z);
    }
    
    DISPATCH(pc+1);

  FOR: {
      auto &source = get_reg(0);

      if (auto [v, e] = source.as(types::Iter::get()).next(); e) {
	return e;
      } else if (v) {
	set_reg(1, *v);
	pc++;
      } else {
	pc = op.as<ops::For>().end_pc;
      }
    }
    
    DISPATCH(pc);

  GET_REG: {
      stack.push(get_reg(op.as<ops::GetReg>().reg));
    }    

    DISPATCH(pc+1);

  GOTO: {}

    DISPATCH(op.as<ops::Goto>().pc);

  ITER: {
      stack.push(stack.pop().iter());
    }
    
    DISPATCH(pc+1);

  MAKE_PAIR: {
      auto right = stack.pop();
      auto &left = stack.peek();
      left = Cell(types::Pair::get(), make_pair(left, right));
    }
    
    DISPATCH(pc+1);

  MAKE_REF: {
      auto &target = stack.peek();
      target = Cell(types::Ref::get(), Ref(target));
    }
    
    DISPATCH(pc+1);

  MAKE_VECTOR: {
      stack.push(types::Vector::get(), types::Vector::Value());
    }
    
    DISPATCH(pc+1);

  PUSH: {
      stack.push(op.as<ops::Push>().value);
    }

    DISPATCH(pc+1);

  PUSH_REGS: {
      const auto
	i = stack.items.end() - op.as<ops::PushRegs>().n,
	j = stack.items.end();

      reverse(i, j);
      move(i, j, back_inserter(regs));
      stack.items.erase(i, j);
    }

    DISPATCH(pc+1);

  PUSH_VALUES: {
      const auto pv = op.as<ops::PushValues>();
      auto &target = get_reg(pv.target_reg);

      struct Rec {
	static void call(const int arity, Cell &target, Stack &stack) {
	  if (arity) {
	    const auto v = stack.pop();
	    call(arity-1, target, stack);
	    target.push(v);
	  }
	}
      };
      
      Rec::call(pv.n, target, stack);
    }

    DISPATCH(pc+1);

  PUSH_VECTOR_ITEM: {
      const auto item = stack.pop();
      stack.peek().as(types::Vector::get()).push_back(item);
    }
    
    DISPATCH(pc+1);

  RECALL: {
      pc++;
      const auto &rc = op.as<ops::Recall>();
      
      if (auto e = call->target.call(*this, 
				     stack, 
				     rc.arity, 
				     rc.loc); e) {
	return e;
      }
    }
    
    DISPATCH(pc);

  RETURN: {
      const auto c = end_call();
      pc = c->ret_pc;
      call_alloc.free(c);
    }

    DISPATCH(pc);

  SET_PATH: {
      path = op.as<ops::SetPath>().path;
    }

    DISPATCH(pc+1);

  SET_REF: {
      const auto v = stack.pop();
      auto &r = stack.peek().as(types::Ref::get());
      r.imp->value = v;
    }

    DISPATCH(pc+1);

  SET_REF_DIRECT: {
      const auto v = stack.pop();
      op.as<ops::SetRefDirect>().target.imp->value = v;
    }

    DISPATCH(pc+1);

  SET_REG: {
      set_reg(op.as<ops::SetReg>().reg, stack.pop());
    }    

    DISPATCH(pc+1);

  STOP: {
      pc++;
      return nullopt;
    }

  TAIL_CALL: {
      auto &tc = op.as<ops::TailCall>();
      regs.erase(regs.begin() + regs.size() - tc.reg_count, regs.end());
      pc = tc.start_pc;
    }

    DISPATCH(pc);

  TODO: {
      pc++;
      return Error(op.as<ops::Todo>().loc, "Todo");
    }

  TRACE: {
      cout << ++pc << ' ';
      ops[pc].trace(cout);
      cout << endl;
    }

    DISPATCH(pc);
  }
}

