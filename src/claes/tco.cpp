#include "claes/ops/call_direct.hpp"
#include "claes/ops/goto.hpp"
#include "claes/ops/recall.hpp"
#include "claes/ops/tail_call.hpp"
#include "claes/vm.hpp"

namespace claes {
  E VM::tco(const Cell &target, 
	    const PC target_pc, 
	    const PC start_pc, 
	    Op *last_call) {
    for (auto pc = start_pc; pc < ops.size();) {
      auto &op = ops[pc];

      switch (op.op_code()) {
      case Op::Code::CALL_DIRECT:
	if (op.as<ops::CallDirect>().target == target) {
	  cout << "RECALL " << target << endl;
	  last_call = &op;
	  const auto &cd = op.as<ops::CallDirect>();
	  op.imp = make_shared<ops::Recall>(cd.arity, cd.loc);
	} else {
	  last_call = nullptr;
	}
		     
	pc++;
	break;
      case Op::Code::GOTO: {
	const auto gpc = op.as<ops::Goto>().pc;
	
	if (gpc > pc) {
	  if (auto e = tco(target, target_pc, gpc, last_call); e) {
	    return e;
	  }
	}
	
	pc++;
	break;
      }
      case Op::Code::RETURN:
	if (last_call) {
	  cout << "TCO " << target << endl;
	  last_call->imp =
	    make_shared<ops::TailCall>(target_pc,
				       last_call->as<ops::Recall>().arity);
	  last_call = nullptr;
	}

	pc++;
	break;
      case Op::Code::TRACE:
	pc++;
	break;
      default:
	last_call = nullptr;
	pc++;
      }
    }
		 
    return nullopt;
  }
}
