#ifndef CLAES_FORM_HPP
#define CLAES_FORM_HPP

#include <set>

#include "claes/error.hpp"
#include "claes/loc.hpp"

namespace claes {
  struct Cell;
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
      virtual void collect_ids(set<string> &out) const = 0;
      virtual void dump(ostream &out) const = 0;
      virtual E emit(VM &vm, Env &env, Forms &args) const = 0;
      virtual E emit_call(VM &vm, Env &env, const Forms &args, const Loc &loc) const;
      virtual E emit_ref(VM &vm, Env &env, Forms &args, const Loc &loc) const;
      virtual Cell quote(VM &vm, int depth) const = 0;
    };

    shared_ptr<const Imp> imp;
    Form(shared_ptr<const Imp> imp): imp(imp) {}

    template <typename T>
    const T *as() const { 
      return dynamic_cast<const T *>(imp.get()); 
    }

    void collect_ids(set<string> &out) const {
      imp->collect_ids(out);
    }

    E emit(VM &vm, Env &env, Forms &args) const {
      return imp->emit(vm, env, args);
    }

    E emit_call(VM &vm, 
		Env &env, 
		const Forms &args, 
		const Loc &loc) const {
      return imp->emit_call(vm, env, args, loc);
    }

    E emit_ref(VM &vm, 
	       Env &env, 
	       Forms &args, 
	       const Loc &loc) const {
      return imp->emit_ref(vm, env, args, loc);
    }

    Cell quote(VM &vm, int depth) const;
  };

  inline ostream &operator<<(ostream &out, const Form &v) {
    v.imp->dump(out);
    return out;
  }
}

#endif
