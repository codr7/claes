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
		     int arity,
		     const Loc &loc) const;

      virtual Cell clone(const Cell &value) const;
      virtual strong_ordering compare(const Cell &left, const Cell &right) const = 0;
      virtual void dump(const Cell &value, ostream &out) const = 0;      

      virtual E emit_call(const Cell &value,
			  VM &vm, 
			  Env &env, 
			  const Forms &args,
			  const Loc &loc) const {
	return Error(loc, "Invalid call target: ", value);
      }

      virtual E emit_id(const Cell &value,
			VM &vm, 
			Env &env, 
			Forms &args,
			const Loc &loc) const {
	return emit_literal(value, vm, env, args, loc);
      }

      virtual E emit_literal(const Cell &value,
			     VM &vm, 
			     Env &env, 
			     Forms &args,
			     const Loc &loc) const;

      virtual bool eq(const Cell &left, const Cell &right) const = 0;

      virtual bool is_true(const Cell &value) const {
	return true;
      }

      virtual void push(Cell &target, const Cell &item) const;
    };

    shared_ptr<const Imp> imp;

    template <typename T>
    Type(shared_ptr<const T> imp): imp(imp) {}

    E call(const Cell &target, 
	   VM &vm, 
	   Stack &stack, 
	   int arity,
	   const Loc &loc) const {
      return imp->call(target, vm, stack, arity, loc);
    }

    Cell clone(const Cell &value) const;

    strong_ordering compare(const Cell &left, const Cell &right) const {
      return imp->compare(left, right);
    }

    void dump(const Cell &value, ostream &out) const {
      imp->dump(value, out);
    }

    E emit_call(const Cell &value,
		VM &vm, 
		Env &env, 
		const Forms &args,
		const Loc &loc) const {
      return imp->emit_call(value, vm, env, args, loc);
    }

    E emit_id(const Cell &value,
	      VM &vm, 
	      Env &env, 
	      Forms &args,
	      const Loc &loc) const {
      return imp->emit_id(value, vm, env, args, loc);
    }

    E emit_literal(const Cell &value,
		   VM &vm, 
		   Env &env, 
		   Forms &args,
		   const Loc &loc) const {
      return imp->emit_literal(value, vm, env, args, loc);
    }
    
    bool eq(const Cell &left, const Cell &right) const {
      return imp->eq(left, right);
    }

    bool is_true(const Cell &value) const {
      return imp->is_true(value);
    }

    void push(Cell &target, const Cell &item) const;
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

  inline strong_ordering operator<=>(const Type &left, const Type &right) {
    return left.imp->name <=> right.imp->name;
  }

  inline ostream &operator <<(ostream &out, const Type &type) {
    out << "(Type " << type.imp->name << ')';
    return out;
  }
}

#endif
