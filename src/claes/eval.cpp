#include <iostream>

#include "claes/error.hpp"
#include "claes/ops/benchmark.hpp"
#include "claes/ops/branch.hpp"
#include "claes/ops/push.hpp"
#include "claes/ops/stop.hpp"
#include "claes/stack.hpp"
#include "claes/timer.hpp"
#include "claes/vm.hpp"

#define DISPATCH(next_pc)						\
  goto *dispatch[static_cast<int>((op = ops[pc = (next_pc)]).op_code())] \

namespace claes {
  using namespace std;
  
  optional<Error> VM::eval(PC start_pc, Stack &stack) {
    static const void* dispatch[] = {
      &&BENCHMARK, &&BRANCH,
	//&&CALL, &&CHECK, 
      //&&DECREMENT, 
      //&&GOTO,
      //&&NOP, 
      &&PUSH,
      //&&RETURN,
      //&&TRACE, 
      &&STOP};

    Op op;
    DISPATCH(start_pc);

  BENCHMARK: {
      auto n = op.as<ops::Benchmark>().repetitions;
      const auto start_pc = pc+1;
      Timer t;

      for (auto i = 0; i < n; i++) {
	Stack s;
	if (auto e = eval(start_pc, s); e) { return e; }
      }

      stack.push(types::i64, t.ms());
      DISPATCH(pc);
    }
    
  BRANCH: {
      DISPATCH(stack.pop().is_true() ? pc+1 : op.as<ops::Branch>().else_pc);
    }

    /*
      CALL: {
      Fun *target = state->get(ops::call_target(op)).as<Fun *>();
      Reg reg = ops::call_reg(op);
      PC ret_pc1 = pc+1;
      
      if (auto [ret_pc2, err] = target->call(reg, ret_pc1, *this); err) {
      return err;
      } else if (ret_pc2 == ret_pc1) {
      ret_state(reg, 0);
      } else {
      ret_pc1 = ret_pc2;
      }
      
      DISPATCH(ret_pc1); 
      }

      CALLI1: {
      Fun *target = ops::calli1_target(op);
      Reg reg = ops::calli1_reg(op);
      PC ret_pc1 = pc+1;
      
      if (auto [ret_pc2, err] = target->call(reg, ret_pc1, *this); err) {
      return err;
      } else if (ret_pc2 == ret_pc1) {
      ret_state(reg, 0);
      } else {
      ret_pc1 = ret_pc2;
      }
	  
      DISPATCH(ret_pc1); 
      }

      COPY:
      state->set(ops::copy_dst(op), state->get(ops::copy_src(op)));
      DISPATCH(pc+1);

      COPYS: {
      Reg di = ops::copy_dst(op), si = ops::copy_src(op);
      int len = ops::copys_len(op);
      for (int i = 0; i < len; i++, di++, si++) { state->set(di, state->get(si)); }
      DISPATCH(pc+1);
      }

      DEC:
      state->set(ops::dec_dst(op),
      Val(abc_lib->int_type,
      state->get(ops::dec_src(op)).as<types::Int::DataType>() - ops::dec_delta(op)));
      
      DISPATCH(pc+1);

      EQ:
      state->set(ops::eq_dst(op),
      Val(abc_lib->bool_type,
      state->get(ops::eq_left(op)) == state->get(ops::eq_right(op))));
      
      DISPATCH(pc+1);

      FUN:
      state->get(ops::fun_reg(op)).as<Fun *>()->state = freeze_state();
      DISPATCH(ops::fun_end(op));

      GOTO:
      DISPATCH(ops::goto_pc(op));

      LOAD_BOOL:
      state->set(ops::load_dst(op), Val(abc_lib->bool_type, ops::load_bool_val(op)));
      DISPATCH(pc+1);

      LOAD_FUN:
      state->set(ops::load_dst(op), Val(abc_lib->fun_type, reinterpret_cast<Fun *>(ops[pc+1])));
      DISPATCH(pc+2);

      LOAD_INT1:
      state->set(ops::load_dst(op), Val(abc_lib->int_type, ops::load_int1_val(op)));
      DISPATCH(pc+1);

      LOAD_INT2:
      state->set(ops::load_dst(op), Val(abc_lib->int_type, static_cast<types::Int::DataType>(ops[pc+1])));
      DISPATCH(pc+2);

      LOAD_MACRO:
      state->set(ops::load_dst(op), Val(abc_lib->macro_type, reinterpret_cast<Macro *>(ops[pc+1])));
      DISPATCH(pc+2);

      LOAD_SYM:
      state->set(ops::load_dst(op), Val(abc_lib->sym_type, syms[ops::load_sym_id(op)]));
      DISPATCH(pc+1);

      LOAD_TYPE:
      state->set(ops::load_dst(op), Val(abc_lib->meta_type, types[ops::load_type_id(op)]));
      DISPATCH(pc+1);

      MOVE:
      state->set(ops::move_dst(op), move(state->get(ops::move_src(op))));
      DISPATCH(pc+1);

      MOVES: {
      Reg di = ops::move_dst(op), si = ops::move_src(op);
      int len = ops::moves_len(op);
      for (int i = 0; i < len; i++, di++, si++) { state->set(di, move(state->get(si))); }
      DISPATCH(pc+1);
      }

      NOP:
      DISPATCH(pc+1);

      ONE:
      state->set(ops::one_dst(op),
      Val(abc_lib->bool_type,
      state->get(ops::one_src(op)).as<types::Int::DataType>() == 1));
      
      DISPATCH(pc+1);

      REC: {
      State *prev = end_state();
      for (Reg i = 1; i < frame->target->arg_count+1; i++) { state->set(i, move(prev->get(i))); }
      deref_state(prev);
      DISPATCH(frame->target->start_pc);
      }*/

  PUSH: {
      stack.push(op.as<ops::Push>().value.clone());
      DISPATCH(pc+1);
    }
  
    /*  
	RET: {
	Frame *f = end_frame();
	PC ret_pc = f->ret_pc;
	Reg reg = ops::ret_reg(op);
	ret_state(reg);
	ret_state(reg);
	if (f->ret_reg != reg) { state->set(f->ret_reg, move(state->get(reg))); }	
	deref_frame(f);
	DISPATCH(ret_pc);
	}

	STATE_BEG:
	for (int i = 0; i < ops::state_beg_count(op); i++) { begin_state(); }
	DISPATCH(ops::state_beg_next(op));

	STATE_END:
	ret_state(ops::state_end_reg(op));
	DISPATCH(pc+1);

	TEST: {
	cout << "Test " << state->get(ops::test_actual(op)) << " = " << state->get(ops::test_expected(op)) << "...";

	if (state->get(ops::test_actual(op)) == state->get(ops::test_expected(op))) {
	state->set(ops::test_result(op), Val(abc_lib->bool_type, true));
	cout << "OK" << endl;
	} else {
	state->set(ops::test_result(op), Val(abc_lib->bool_type, false));
	cout << "FAIL" << endl;
	}
      
	DISPATCH(pc+1);
	}

	TRACE:
	op_trace(pc+1, cout, *this);
	DISPATCH(pc+1);
    
	Z:
	state->set(ops::z_dst(op), Val(abc_lib->bool_type, state->get(ops::z_src(op)).as<types::Int::DataType>() == 0));
	DISPATCH(pc+1);
    */

  STOP:
    return nullopt;
  }
}

