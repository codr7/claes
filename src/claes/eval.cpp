#include <iostream>

#include "claes/error.hpp"
#include "claes/ops/benchmark.hpp"
#include "claes/ops/branch.hpp"
#include "claes/ops/call_direct.hpp"
#include "claes/ops/call_indirect.hpp"
#include "claes/ops/check.hpp"
#include "claes/ops/get_reg.hpp"
#include "claes/ops/goto.hpp"
#include "claes/ops/push.hpp"
#include "claes/ops/set_path.hpp"
#include "claes/ops/set_reg.hpp"
#include "claes/ops/stop.hpp"
#include "claes/ops/todo.hpp"
#include "claes/stack.hpp"
#include "claes/timer.hpp"
#include "claes/types/pair.hpp"
#include "claes/types/vector.hpp"
#include "claes/vm.hpp"

#define DISPATCH(next_pc)						\
  goto *dispatch[static_cast<int>((op = ops[(pc = (next_pc))]).op_code())]

namespace claes {
  using namespace std;
  
  E VM::eval(const PC start_pc, Stack &stack) {
    static const void* dispatch[] = {
      &&BEGIN_FRAME, &&BENCHMARK, &&BRANCH,
	&&CALL_DIRECT, &&CALL_INDIRECT, &&CHECK,
	&&END_FRAME,
	&&GET_REG, &&GOTO,
	&&MAKE_PAIR, &&MAKE_VECTOR,
	&&PUSH, &&PUSH_ITEM, &&PUSH_REG,
	&&RETURN,
	&&SET_PATH, &&SET_REG, &&STOP,
	&&TODO, &&TRACE};

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

      if (auto e = cd.target.call(*this, stack, cd.arity, cd.loc); e) {
	return e;
      }
    }
    
    DISPATCH(pc);

  CALL_INDIRECT: {
      const auto &ci = op.as<ops::CallIndirect>();
      const auto target = stack.pop();
      pc++;

      if (auto e = target.call(*this, stack, ci.arity, ci.loc); e) {
	return e;
      }
    }
    
    DISPATCH(pc);

  CHECK: {
      const auto expected = stack.pop();
      Stack s;
      eval(pc+1, s);
      const auto actual = s.pop();

      if (actual != expected) {
	return Error(op.as<ops::Check>().loc, 
		     "Check failed; expected ", expected, ", actual ", actual);
      }
    }

    DISPATCH(pc);

  END_FRAME: {
      end_frame();
    }
    
    DISPATCH(pc+1);

  GET_REG: {
      stack.push(*get_reg(op.as<ops::GetReg>().reg));
    }    

    DISPATCH(pc+1);

  GOTO: {}

    DISPATCH(op.as<ops::Goto>().pc);

  MAKE_PAIR: {
      auto right = stack.pop();
      auto left = stack.pop();
      stack.push(types::Pair::get(), make_pair(left, right));
    }
    
    DISPATCH(pc+1);

  MAKE_VECTOR: {
      stack.push(types::Vector::get(), types::Vector::Value());
    }
    
    DISPATCH(pc+1);

  PUSH: {
      stack.push(op.as<ops::Push>().value.clone());
    }

    DISPATCH(pc+1);

  PUSH_ITEM: {
      const auto item = stack.pop();
      stack.peek().as(types::Vector::get()).imp->items.push_back(item);
    }
    
    DISPATCH(pc+1);

  PUSH_REG: {
      push_reg(stack.pop());
    }

    DISPATCH(pc+1);

  RETURN: {
      auto c = end_call();
      pc = c->ret_pc;
      call_alloc.free(c);
    }

    DISPATCH(pc);

  SET_PATH: {
      path = op.as<ops::SetPath>().path;
    }

    DISPATCH(pc+1);

  SET_REG: {
      set_reg(op.as<ops::GetReg>().reg, stack.pop());
    }    

    DISPATCH(pc+1);

  STOP: {
      pc++;
      return nullopt;
    }

  TODO: {
      pc++;
      return Error(op.as<ops::Todo>().loc, "Todo");
    }

  TRACE: {
      cout << pc << ' ';
      ops[++pc].trace(cout);
      cout << endl;
    }

    DISPATCH(pc);
  }
}

