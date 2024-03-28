#include "claes/forms/id.hpp"
#include "claes/forms/literal.hpp"
#include "claes/forms/quote.hpp"
#include "claes/forms/splat.hpp"
#include "claes/forms/vector.hpp"
#include "claes/libs/core.hpp"
#include "claes/ops/begin_frame.hpp"
#include "claes/ops/benchmark.hpp"
#include "claes/ops/branch.hpp"
#include "claes/ops/call_direct.hpp"
#include "claes/ops/check.hpp"
#include "claes/ops/decrement.hpp"
#include "claes/ops/end_frame.hpp"
#include "claes/ops/exit.hpp"
#include "claes/ops/for.hpp"
#include "claes/ops/goto.hpp"
#include "claes/ops/iter.hpp"
#include "claes/ops/push.hpp"
#include "claes/ops/push_regs.hpp"
#include "claes/ops/push_values.hpp"
#include "claes/ops/recall.hpp"
#include "claes/ops/return.hpp"
#include "claes/ops/set_reg.hpp"
#include "claes/ops/stop.hpp"
#include "claes/ops/tail_call.hpp"
#include "claes/ops/todo.hpp"
#include "claes/stack.hpp"
#include "claes/types/bit.hpp"
#include "claes/types/expr.hpp"
#include "claes/types/i64.hpp"
#include "claes/types/iter.hpp"
#include "claes/types/loc.hpp"
#include "claes/types/meta.hpp"
#include "claes/types/macro.hpp"
#include "claes/types/method.hpp"
#include "claes/types/nil.hpp"
#include "claes/types/pair.hpp"
#include "claes/types/path.hpp"
#include "claes/types/ref.hpp"
#include "claes/types/reg.hpp"
#include "claes/types/string.hpp"
#include "claes/types/sym.hpp"
#include "claes/types/vector.hpp"
#include "claes/vm.hpp"

namespace claes::libs {
  Core::Core(): Env() {
    bind_type(types::Bit::get());
    bind_type(types::Expr::get());
    bind_type(types::I64::get());
    bind_type(types::Iter::get());
    bind_type(types::Loc::get());
    bind_type(types::Meta::get());
    bind_type(types::Macro::get());
    bind_type(types::Method::get());
    bind_type(types::Nil::get());
    bind_type(types::Pair::get());
    bind_type(types::Path::get());
    bind_type(types::Ref::get());
    bind_type(types::Reg::get());
    bind_type(types::Rune::get());
    bind_type(types::String::get());
    bind_type(types::Sym::get());
    bind_type(types::Vector::get());

    bind("_", NIL());
    bind("T", T());
    bind("F", F());

    bind_method("+", {"x"},
		[](const Method &self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const Loc &loc) -> E {
		  types::I64::Value v = 0;
		  
		  while (--arity) {
		    v += stack.pop().as(types::I64::get());
		  }

		  auto &s = stack.peek();
		  s = Cell(types::I64::get(), v + s.as(types::I64::get()));
		  return nullopt;
		});

    bind_method("-", {"x"},
		[](const Method &self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const Loc &loc) -> E {
		  types::I64::Value v = 0;

		  while (--arity) {
		    const auto a = stack.pop().as(types::I64::get());
		    v -= a;
		  }

		  auto &s = stack.peek();
		  s = Cell(types::I64::get(), v + s.as(types::I64::get()));
		  return nullopt;
		});

    bind_method("=", {"x", "y"},
		[](const Method &self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const Loc &loc) -> E {
		  auto v = stack.pop();
		  auto result = true;
		  arity--;

		  while (--arity) {
		    if (stack.pop() != v) {
		      result = false;
		      break;
		    }
		  }

		  auto &s = stack.peek();
		  s = Cell(types::Bit::get(), result && s == v);
		  return nullopt;
		});

    bind_method("<", {"x", "y"},
		[](const Method &self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const Loc &loc) -> E {
		  auto v = stack.pop();
		  auto result = true;
		  arity--;

		  while(--arity) {
		    if (const auto nv = stack.pop(); nv >= v) {
		      result = false;
		    } else {
		      v = nv;
		    }
		  }

		  auto &nv = stack.peek();
		  nv = Cell(types::Bit::get(), result && nv < v);
		  return nullopt;
		});

    bind_method(">", {"x", "y"},
		[](const Method &self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const Loc &loc) -> E {
		  auto v = stack.pop();
		  auto result = true;
		  arity--;

		  while(--arity) {
		    if (const auto nv = stack.pop(); nv <= v) {
		      result = false;
		      break;
		    } else {
		      v = nv;
		    }
		  }

		  auto &nv = stack.peek();
		  nv = Cell(types::Bit::get(), result && nv > v);		      
		  return nullopt;
		});

    bind_macro("^", 1,
	       [](const Macro &self, 
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
		 vector<string> arg_names;

		 for (auto a = method_args.items.rbegin(); 
		      a != method_args.items.rend(); 
		      a++) {
		   if (auto id = a->as<forms::Id>(); id) {
		     const auto &name = a->as<forms::Id>()->name;
		     arg_names.push_back(name);
		   } else if (auto q = a->as<forms::Quote>(); q) {
		     if (auto id = q->target.as<forms::Id>(); id) {
		       const auto name = to_string('\'', id->name);
		       arg_names.push_back(name);
		     } else {
		       return Error(loc, "Invalid argument: ", q->target);
		     }
		   } else if (auto s = a->as<forms::Splat>(); s) {
		     if (auto id = s->target.as<forms::Id>(); id) {
		       const auto name = to_string(id->name, '*');
		       arg_names.push_back(name);
		     } else {
		       return Error(loc, "Invalid argument: ", q->target);
		     }
		   } else {
		     return Error(loc, "Invalid argument: ", *a);
		   }
		 }

		 Method method(name ? *name : "lambda", 		
			       arg_names,
			       [start_pc](const Method &self, 
					  VM &vm, 
					  Stack &stack, 
					  int arity,
					  bool recursive,
					  const Loc &loc) -> E { 
				 const auto target = Cell(types::Method::get(), self);
				 vm.begin_call(target, recursive, loc);
				 vm.pc = start_pc;
				 return nullopt;
			       });
		 
		 if (name) {
		   env.bind(method.imp->name, 
			    Cell(types::Method::get(), method));
		 }

		 set<string> body_ids;
		 my_args.collect_ids(body_ids);
		 Env body_env(env.imp, body_ids);
		 auto reg_count = 0;
		 
		 for (auto n: arg_names) {
		   if (n.front() == '\'') {
		     n = n.substr(1);
		   }

		   if (n.back() == '*') {
		     n.pop_back();
		   }
		   
		   body_env.bind(n, types::Reg::get(), reg_count++);
		 }
		 
		 vm.emit<ops::PushRegs>(reg_count);

		 if (auto e = my_args.emit(vm, body_env); e) {
		   return e;
		 }

		 vm.emit<ops::Return>();
		 vm.ops[skip_pc].imp = make_shared<ops::Goto>(vm.emit_pc());

		 auto mv = Cell(types::Method::get(), method);
		 
		 if (!name) {
		   vm.emit<ops::Push>(mv);
		 }

		 return vm.tco(mv, start_pc, start_pc);
	       });

    bind_method("apply", {"target", "args"},
		[](const Method &self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const Loc &loc) -> E {
		  auto it = stack.pop().iter().as(types::Iter::get());
		  arity -= 2;

		  rotate(stack.begin(),
			 stack.begin() + stack.len() - arity,
			 stack.end());

		  auto t = stack.pop();

		  for (;;) {
		    const auto [v, e] = it.next();

		    if (e) {
		      return e;
		    }

		    if (!v) {
		      break;
		    }

		    stack.push(*v);
		    arity++;
		  }

		  return t.call(vm, stack, arity, recursive, loc);
		});
    
    bind_macro("benchmark", 1, 
	       [](const Macro &self, 
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
		 set<string> body_ids;
		 my_args.collect_ids(body_ids);
		 Env body_env(env.imp, body_ids);
		 
		 if (auto e = my_args.emit(vm, body_env); e) {
		   return e;
		 }
		 
		 vm.emit<ops::Exit>();
		 return nullopt;
	       });

    bind_macro("check", 2, 
	       [](const Macro &self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);
		   
		 if (auto e = my_args.pop().emit(vm, env, my_args); e) {
		   return e;
		 }

		 vm.emit<ops::Check>(loc);
		 set<string> body_ids;
		 my_args.collect_ids(body_ids);
		 Env body_env(env.imp, body_ids);

		 if (auto e = my_args.emit(vm, body_env); e) {
		   return e;
		 }
		   
		 vm.emit<ops::Exit>();
		 return nullopt;
	       });

    bind_macro("debug", 0, 
	       [](const Macro &self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) {
		 vm.debug = !vm.debug;
		 vm.emit<ops::Push>(vm.debug ? T() : F());
		 return nullopt;
	       });

    bind_macro("decr", 1, 
	       [](const Macro &self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);
		 const auto target_form = my_args.pop();
		 const auto target_name = target_form.as<forms::Id>()->name;
		 const auto target = env.find(target_name);
		 
		 if (!target) {
		   return Error(loc, "Unknown decrement target: ", target_name);
		 }

		 if (target->type != types::Reg::get()) {
		   return Error(loc, "Invalid decrement target: ", *target);
		 }

		 vm.emit<ops::Decrement>(target->as(types::Reg::get()));
		 return nullopt;
	       });

    bind_macro("define", 2, 
	       [](const Macro &self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);

		 for (auto bf = my_args.begin(); 
		      bf != my_args.end(); 
		      bf++) {
		   const auto &name_form = *bf;
		   const auto &value_form = *(++bf);
		   auto [v, e] = vm.eval(value_form, env);

		   if (e) {
		     return e;
		   }

		   if (!v) {
		     return Error(loc, "Invalid binding");
		   }
		   
		   env.bind(name_form.as<forms::Id>()->name, *v);
		 }

		 return nullopt;
	       });
    
    bind_macro("do", 0, 
	       [](const Macro &self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);
		 return my_args.emit(vm, env);
	       });
    
    bind_method("dump", {"value"},
		[](const Method &self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const Loc &loc) -> E {
		  struct Rec {
		    static void call(Stack &stack, const int i, const int max) {
		      if (i < max) {
			const auto v = stack.pop();
			call(stack, i+1, max);

			if (i != max-1) {
			  cout << ' ' << v;
			} else {
			  cout << v;
			}
		      }
		    }
		  };
		  
		  Rec::call(stack, 0, arity);
		  cout << endl;
		  return nullopt;
		});

    bind_macro("for", 2, 
	       [](const Macro &self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);
		 const auto var_form = my_args.pop();
		 const auto var_id = var_form.as<forms::Id>();

		 if (!var_id) {
		   return Error(loc, "Expected identifier: ", var_form);
		 }


		 vm.emit<ops::Push>(NIL());

		 if (auto e = my_args.pop().emit(vm, env, my_args); e) {
		   return e;
		 }

		 vm.emit<ops::Iter>();
		 vm.emit<ops::BeginFrame>();
		 set<string> body_ids;
		 my_args.collect_ids(body_ids);
		 Env body_env(env.imp, body_ids);
		 body_env.bind(var_id->name, Cell(types::Reg::get(), Reg(1)));
		 vm.emit<ops::PushRegs>(2);		 
		 const auto for_pc = vm.emit<ops::Todo>(loc);

		 if (auto e = my_args.emit(vm, body_env); e) {
		   return e;
		 }
		 
		 vm.emit<ops::Goto>(for_pc);
		 vm.ops[for_pc].imp = make_shared<ops::For>(vm.emit_pc());
		 vm.emit<ops::EndFrame>();
		 return nullopt;
	       });

    bind_macro("if", 2, 
	       [](const Macro &self, 
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

    bind_macro("iter", 1, 
	       [](const Macro &self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);
		 
		 if (auto e = my_args.pop().emit(vm, env, my_args); e) {
		   return e;
		 }

		 vm.emit<ops::Iter>();
		 return nullopt;
	       });


    bind_macro("let", 1, 
	       [](const Macro &self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);
		 const auto &binding_forms = 
		   my_args.pop().as<forms::Vector>()->items;
		 set<string> body_ids;

		 for (auto bf = binding_forms.begin(); 
		      bf != binding_forms.end(); 
		      bf ++) {
		   bf->collect_ids(body_ids);
		 }

		 my_args.collect_ids(body_ids);
		 vm.emit<ops::BeginFrame>();
		 Env body_env(env.imp, body_ids);
		 auto reg_count = 0;

		 for (auto bf = binding_forms.begin(); 
		      bf != binding_forms.end(); 
		      bf++) {
		   const auto &name_form = *bf;
		   const auto &value_form = *(++bf);

		   body_env.bind(name_form.as<forms::Id>()->name, 
				 Cell(types::Reg::get(), reg_count++));

		   Forms value_args;

		   if (auto e = value_form.emit(vm, body_env, value_args); e) {
		     return e;
		   }

		   vm.emit<ops::PushRegs>(1);
		 }

		 if (auto e = my_args.emit(vm, body_env); e) {
		   return e;
		 }

		 vm.emit<ops::EndFrame>();
		 return nullopt;
	       });

    bind_method("loc", {},
		[](const Method &self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const Loc &loc) -> E {
		  if (vm.loc) {
		    stack.push(types::Loc::get(), *vm.loc);
		  } else {
		    stack.push(NIL());
		  }

		  return nullopt;
		});

    bind_macro("load", 1, 
	       [](const Macro &self, 
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

    bind_method("path", {"value"},
		[](const Method &self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const Loc &loc) -> E {
		  auto &v = stack.peek();
		  v = Cell(types::Path::get(), v.as(types::String::get()));
		  return nullopt;
		});

    bind_macro("push", 2, 
	       [](const Macro &self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);
		 const auto target_form = my_args.pop();
		 const auto target_name = target_form.as<forms::Id>()->name;
		 const auto target = env.find(target_name);

		 if (!target) {
		   return Error(loc, "Unknown push destination: ", target_name);
		 }

		 if (target->type != types::Reg::get()) {
		   return Error(loc, "Invalid push destination: ", *target);
		 }

		 const auto arity = my_args.len();

		 if (auto e = my_args.emit(vm, env); e) {
		   return e;
		 }

		 vm.emit<ops::PushValues>(target->as(types::Reg::get()), arity);
		 return nullopt;
	       });
    
    bind_method("say", {"value"},
		[](const Method &self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const Loc &loc) -> E {
		  struct Rec {
		    static void call(Stack &stack, const int i, const int max) {
		      if (i < max) {
			const auto v = stack.pop();
			call(stack, i+1, max);

			if (i != max-1) {
			  cout << ' ';
			} 

			v.say(cout);
		      }
		    }
		  };
		  
		  Rec::call(stack, 0, arity);
		  cout << endl;
		  return nullopt;
		});

    bind_macro("set", 2, 
	       [](const Macro &self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 Forms my_args(args);

		 for (auto a = my_args.begin(); 
		      a != my_args.end();) {
		   const auto &name_form = *a++;
		   const auto &name = name_form.as<forms::Id>()->name;
		   auto v = env.find(name);

		   if (!v) {
		     return Error(loc, "Unknown identifier: ", name);
		   }
		   
		   if (v->type != types::Reg::get()) {
		     return Error(loc, "Expected register: ", *v);
		   }

		   const auto &value_form = *a++;		   
		   Forms value_args;

		   if (auto e = value_form.emit(vm, env, value_args); e) {
		     return e;
		   }

		   vm.emit<ops::SetReg>(v->as(types::Reg::get()));
		 }

		 return nullopt;
	       });

    bind_macro("stop", 0, 
	       [](const Macro &self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) -> E {
		 vm.emit<ops::Stop>();
		 return nullopt;
	       });
    
    bind_macro("trace", 0, 
	       [](const Macro &self, 
		  VM &vm, 
		  Env &env, 
		  const Forms &args, 
		  const Loc &loc) {
		 vm.trace = !vm.trace;
		 vm.emit<ops::Push>(vm.trace ? T() : F());
		 return nullopt;
	       });

    bind_method("z?", {"value"},
		[](const Method &self, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const Loc &loc) -> E {
		  auto &v = stack.peek();
		  v = Cell(types::Bit::get(), !v.as(types::I64::get()));
		  return nullopt;
		});
  }
}
