#ifndef CLAES_FORM_HPP
#define CLAES_FORM_HPP

#include <deque>
#include "claes/error.hpp"
#include "claes/loc.hpp"

namespace claes {
  struct Env;
  struct Forms;
  struct VM;

  struct Form {
    template <typename T, typename...Args>
    static Form make(const Loc &loc, Args&&...args) {
      return Form(make_shared<T>(loc, std::forward<Args>(args)...));
    };
      
    struct Imp {
      Loc loc;
      Imp(const Loc &loc): loc(loc) {}
      virtual ~Imp() {}
      virtual E emit(VM &vm, Env &env, Forms &arguments) const = 0;

      virtual E emit_call(VM &vm, 
			  Env &env, 
			  const Forms &arguments, 
			  const Loc &loc) const;
    };

    shared_ptr<const Imp> imp;
    Form(shared_ptr<const Imp> imp): imp(imp) {}

    template <typename T>
    const T &as() const { 
      return *static_cast<const T *>(imp.get()); 
    }

    E emit(VM &vm, Env &env, Forms &arguments) const {
      return imp->emit(vm, env, arguments);
    }

    E emit_call(VM &vm, 
		Env &env, 
		const Forms &arguments, 
		const Loc &loc) const {
      return imp->emit_call(vm, env, arguments, loc);
    }
  };

  struct Forms {
    deque<Form> items;
    
    E emit(VM &vm, Env &env) {
      while (!empty()) {
	if (auto e = pop().emit(vm, env, *this); e) {
	  return e;
	}
      }

      return nullopt;
    }

    bool empty() const {
      return items.empty();
    }

    Form peek() const {
      return items.front();
    }
    
    Form pop() {
      auto f = peek();
      items.pop_front();
      return f;
    }
    
    template <typename T, typename...Args>
    Form push(const Loc loc, Args&&...args) {
      return items.emplace_back(make_shared<T>(loc, std::forward<Args>(args)...));
    }
  };
}

#endif
