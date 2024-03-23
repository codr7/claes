#ifndef CLAES_FORM_HPP
#define CLAES_FORM_HPP

#include <deque>
#include <set>

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
      virtual void collect_ids(set<string> &out) const = 0;
      virtual void dump(ostream &out) const = 0;
      virtual E emit(VM &vm, Env &env, Forms &args) const = 0;
      virtual E emit_call(VM &vm, Env &env, const Forms &args, const Loc &loc) const;
      virtual E emit_ref(VM &vm, Env &env, Forms &args, const Loc &loc) const;
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
  };

  inline ostream &operator<<(ostream &out, const Form &v) {
    v.imp->dump(out);
    return out;
  }

  struct Forms {
    deque<Form> items;

    void collect_ids(set<string> &out) const {
      for (const auto &f: items) {
	f.collect_ids(out);
      }
    }

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

    Form pop_back() {
      auto f = items.back();
      items.pop_back();
      return f;
    }
    
    template <typename T, typename...Args>
    Form push(const Loc loc, Args&&...args) {
      return items.emplace_back(make_shared<T>(loc, std::forward<Args>(args)...));
    }
  };

  inline ostream &operator<<(ostream &out, const Forms &fs) {
    auto i = 0;

    for (const auto &f: fs.items) {
      if (i++) {
	out << ' ';
      }

      f.imp->dump(out);
    }

    return out;
  }

}

#endif
