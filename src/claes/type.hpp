#ifndef CLAES_TYPE_HPP
#define CLAES_TYPE_HPP

#include <string>
#include "claes/error.hpp"

namespace claes {
  using namespace std;

  struct Cell;
  struct Env;
  struct Forms;
  struct Stack;
  struct VM;
  
  struct Type {
    struct Imp {
      string name;
      Imp(const string &name): name(name) {}
      virtual ~Imp() {}

      virtual E call(const Cell &target, 
		     VM &vm, 
		     Stack &stack, 
		     const Location &location) const;

      virtual Cell clone(const Cell &value) const;
      virtual void dump(const Cell &value, ostream &out) const = 0;      

      virtual E emit_call(const Cell &value,
			  VM &vm, 
			  Env &env, 
			  const Forms &arguments,
			  const Location &location) const {
	return Error(location, "Invalid call target: ", value);
      }

      virtual E emit_id(const Cell &value,
			VM &vm, 
			Env &env, 
			Forms &arguments,
			const Location &location) const {
	return emit_literal(value, vm, env, arguments, location);
      }

      virtual E emit_literal(const Cell &value,
			     VM &vm, 
			     Env &env, 
			     Forms &arguments,
			     const Location &location) const;

      virtual bool eq(const Cell &left, const Cell &right) const = 0;

      virtual bool is_true(const Cell &value) const {
	return true;
      }
    };

    shared_ptr<const Imp> imp;

    template <typename T>
    Type(shared_ptr<const T> imp): imp(imp) {}

    E call(const Cell &target, 
	   VM &vm, 
	   Stack &stack, 
	   const Location &location) const {
      return imp->call(target, vm, stack, location);
    }

    Cell clone(const Cell &value) const;

    void dump(const Cell &value, ostream &out) const {
      imp->dump(value, out);
    }

    E emit_call(const Cell &value,
		VM &vm, 
		Env &env, 
		const Forms &arguments,
		const Location &location) const {
      return imp->emit_call(value, vm, env, arguments, location);
    }

    E emit_id(const Cell &value,
	      VM &vm, 
	      Env &env, 
	      Forms &arguments,
	      const Location &location) const {
      return imp->emit_id(value, vm, env, arguments, location);
    }

    E emit_literal(const Cell &value,
		   VM &vm, 
		   Env &env, 
		   Forms &arguments,
		   const Location &location) const {
      return imp->emit_literal(value, vm, env, arguments, location);
    }
    
    bool eq(const Cell &left, const Cell &right) const {
      return imp->eq(left, right);
    }

    bool is_true(const Cell &value) const {
      return imp->is_true(value);
    }
  };

  inline bool operator ==(const Type &left, const Type &right) {
    return left.imp.get() == right.imp.get();
  }

  template <typename T> 
  struct TType: Type {
    template <typename...Args>
    TType(const string &name, Args&&...args):
      Type(make_shared<const T>(name, std::forward<Args>(args)...)) {}
  };

  inline ostream &operator <<(ostream &out, const Type &type) {
    out << "(Type " << type.imp->name << ')';
    return out;
  }
}

#endif
