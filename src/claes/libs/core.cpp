#include "claes/forms/id.hpp"
#include "claes/forms/vector.hpp"
#include "claes/libs/core.hpp"
#include "claes/ops/begin_frame.hpp"
#include "claes/ops/benchmark.hpp"
#include "claes/ops/branch.hpp"
#include "claes/ops/check.hpp"
#include "claes/ops/end_frame.hpp"
#include "claes/ops/goto.hpp"
#include "claes/ops/push.hpp"
#include "claes/ops/push_reg.hpp"
#include "claes/ops/return.hpp"
#include "claes/ops/set_reg.hpp"
#include "claes/ops/stop.hpp"
#include "claes/ops/todo.hpp"
#include "claes/stack.hpp"
#include "claes/types/bit.hpp"
#include "claes/types/i64.hpp"
#include "claes/types/meta.hpp"
#include "claes/types/macro.hpp"
#include "claes/types/method.hpp"
#include "claes/types/nil.hpp"
#include "claes/types/pair.hpp"
#include "claes/types/path.hpp"
#include "claes/types/reg.hpp"
#include "claes/types/string.hpp"
#include "claes/types/vector.hpp"
#include "claes/vm.hpp"

namespace claes::libs {
  Core::Core(): Env() {
    bind_type(types::Bit::get());
    bind_type(types::I64::get());
    bind_type(types::Meta::get());
    bind_type(types::Macro::get());
    bind_type(types::Method::get());
    bind_type(types::Nil::get());
    bind_type(types::Pair::get());
    bind_type(types::Path::get());
    bind_type(types::Reg::get());
    bind_type(types::String::get());
    bind_type(types::Vector::get());

    bind("_", types::Nil::get(), nullptr);
    bind("T", types::Bit::get(), true);
    bind("F", types::Bit::get(), false);

    bind_method("+", 
		[](const Method self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   const Loc &loc) -> E {
		  types::I64::Value v = 0;
		    
		  while (arity--) {
		    v += stack.pop().as(types::I64::get());
		  }

		  stack.push(types::I64::get(), v);
		  return nullopt;
		});

    bind_method("=", 
		[](const Method self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   const Loc &loc) -> E {
		  auto v = stack.pop();
		  auto result = true;
		  arity--;

		  while (arity--) {
		    if (stack.pop() != v) {
		      result = false;
		      break;
		    }
		  }

		  stack.push(types::Bit::get(), result);
		  return nullopt;
		});

    bind_method("<", 
		[](const Method self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   const Loc &loc) -> E {
		  auto v = stack.pop();
		  auto result = true;
		  arity--;

		  while(arity--) {
		    if (const auto nv = stack.pop(); v <= nv) {
		      result = false;
		      break;
		    } else {
		      v = nv;
		    }
		  }

		  stack.push(types::Bit::get(), result);
		  return nullopt;
		});

    bind_method(">", 
		[](const Method self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   const Loc &loc) -> E {
		  auto v = stack.pop();
		  auto result = true;
		  arity--;

		  while(arity--) {
		    if (const auto nv = stack.pop(); v >= nv) {
		      result = false;
		      break;
		    } else {
		      v = nv;
		    }
		  }

		  stack.push(types::Bit::get(), result);
		  return nullopt;
		});

    bind_macro("^", 
	       [](const Macro self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);
		 optional<string> name;
		 auto f = my_args.peek();

		 if (auto idf = f.as<forms::Id>(); idf) {
		   name = idf->name;
		   my_args.pop();
		 } 

		 Forms method_args = my_args.pop().as<forms::Vector>()->items;
		 const auto skip_pc = vm.emit<ops::Todo>(loc);
		 const auto start_pc = vm.emit_pc();

		 Method method(name ? *name : "lambda", 		
			       [start_pc](const Method self, 
				  VM &vm, 
				  Stack &stack, 
				  int arity,
				  const Loc &loc) -> E { 
				 const auto target = Cell(types::Method::get(), self);
				 vm.begin_call(target, loc, vm.pc);
				 vm.pc = start_pc;
				 return nullopt;
			       });
		 
		 if (name) {
		   env.bind(method.imp->name, 
			    Cell(types::Method::get(), method));
		 }

		 Env body_env(env.imp);
		 
		 for (auto p = body_env.imp->parent; p; p = p->parent) {
		   for (auto b: p->bindings) {
		     if (b.second.type == types::Reg::get()) {
		       auto v = b.second.as(types::Reg::get());
		       v.frame_offset++;

		       if (body_env.imp->bindings.find(b.first) == 
			   body_env.imp->bindings.end()) {
			 body_env.bind(b.first, Cell(types::Reg::get(), v));
		       }
		     }
		   }
		 }

		 vm.begin_frame();

		 for (auto a = method_args.items.rbegin(); 
		      a != method_args.items.rend(); 
		      a++) {
		   const auto name = a->as<forms::Id>()->name;
		   const auto reg = vm.push_reg();
		   body_env.bind(name, types::Reg::get(), reg);
		   vm.emit<ops::PushReg>();
		 }

		 vm.end_frame();

		 if (auto e = my_args.emit(vm, body_env); e) {
		   return e;
		 }

		 vm.emit<ops::Return>();
		 vm.ops[skip_pc].imp = make_shared<ops::Goto>(vm.emit_pc());
		 
		 if (!name) {
		   vm.emit<ops::Push>(Cell(types::Method::get(), method));
		 }

		 return nullopt;
	       });

    bind_macro("benchmark", 
	       [](const Macro self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);
		 Stack stack;

		 if (auto e = vm.eval(args.peek(), env, stack); e) {
		   return e;
		 }
		 
		 const auto n = stack.pop().as(types::I64::get());
		 vm.emit<ops::Benchmark>(n);  
		 Env body_env(env.imp);
		 
		 if (auto e = my_args.emit(vm, body_env); e) {
		   return e;
		 }
		 
		 vm.emit<ops::Stop>();
		 return nullopt;
	       });

    bind_macro("check", 
	       [](const Macro self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);
		   
		 if (auto e = my_args.pop().emit(vm, env, my_args); e) {
		   return e;
		 }

		 vm.emit<ops::Check>(loc);
		 Env body_env(env.imp);

		 if (auto e = my_args.emit(vm, body_env); e) {
		   return e;
		 }
		   
		 vm.emit<ops::Stop>();
		 return nullopt;
	       });

    bind_macro("if", 
	       [](const Macro self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);
		   
		 if (auto e = my_args.pop().emit(vm, env, my_args); e) {
		   return e;
		 }

		 const auto if_pc = vm.emit<ops::Todo>(loc);
		 
		 if (auto e = my_args.pop().emit(vm, env, my_args); e) {
		   return e;
		 }

		 const optional<PC> skip_pc = my_args.empty() 
		   ? -1 
		   : vm.emit<ops::Todo>(loc);

		 vm.ops[if_pc].imp = make_shared<ops::Branch>(vm.emit_pc());
		 
		 if (skip_pc) {
		   if (auto e = my_args.pop().emit(vm, env, my_args); e) {
		     return e;
		   }

		   vm.ops[*skip_pc].imp = make_shared<ops::Goto>(vm.emit_pc());
		 }

		 return nullopt;
	       });

    bind_macro("let", 
	       [](const Macro self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);
		 const auto &binding_forms = 
		   my_args.pop().as<forms::Vector>()->items;
		 vm.emit<ops::BeginFrame>();
		 Env body_env(env.imp);
		 auto i = 0;

		 for (auto bf = binding_forms.items.begin(); 
		      bf != binding_forms.items.end(); 
		      bf++) {
		   const auto &name_form = *bf;
		   const auto &value_form = *(++bf);

		   body_env.bind(name_form.as<forms::Id>()->name, 
				 Cell(types::Reg::get(), i++));

		   Forms value_args;

		   if (auto e = value_form.emit(vm, body_env, value_args); e) {
		     return e;
		   }

		   vm.emit<ops::PushReg>();
		 }
 		 
		 for (auto p = body_env.imp->parent; p; p = p->parent) {
		   for (auto b: p->bindings) {
		     if (b.second.type == types::Reg::get()) {
		       auto v = b.second.as(types::Reg::get());
		       v.frame_offset++;

		       if (body_env.imp->bindings.find(b.first) == 
			   body_env.imp->bindings.end()) {
			 body_env.bind(b.first, Cell(types::Reg::get(), v));
		       }
		     }
		   }
		 }

		 if (auto e = my_args.emit(vm, body_env); e) {
		   return e;
		 }

		 vm.emit<ops::EndFrame>();
		 return nullopt;
	       });

    bind_macro("load", 
	       [](const Macro self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) {
		 Stack stack;
		 
		 if (auto e = vm.eval(args.peek(), env, stack); e) {
		   return e;
		 }
		 
		 const auto path = stack.pop().as(types::Path::get());
		 return vm.load(path, env, loc);
	       });

    bind_method("path", 
		[](const Method self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   const Loc &loc) -> E {
		  const auto s = stack.pop().as(types::String::get());
		  stack.push(types::Path::get(), s);
		  return nullopt;
		});

    bind_method("say", 
		[](const Method self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   const Loc &loc) -> E {
		  for (int i = 0; i < arity; i++) {
		    if (i) {
		      cout << ' ';
		    }
		    
		    cout << stack.pop();
		  }
 
		  cout << endl;
		  return nullopt;
		});

    bind_macro("trace", 
	       [](const Macro self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) {
		 vm.trace = !vm.trace;
		 vm.emit<ops::Push>(Cell(types::Bit::get(), vm.trace));
		 return nullopt;
	       });
  }
}
