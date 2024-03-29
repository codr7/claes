#ifndef CLAES_CELL_HPP
#define CLAES_CELL_HPP

#include <any>
#include "claes/type.hpp"

namespace claes {
  using namespace std;

  struct Cell {
    Type type;
    any value;

    template <typename T, typename V>
    Cell(const TType<T> &type, const V &value): 
      type(type), value(static_cast<T::Value>(value)) {}

    Cell(const Cell &source): 
      type(source.type), value(source.value) {}
    
    const Cell &operator=(const Cell &source) {
      type = source.type;
      value = source.value;
      return *this;
    }

    template <typename T>
    typename T::Value &as(const TType<T> &type) { 
      return any_cast<typename T::Value &>(value); 
    }

    template <typename T>
    const typename T::Value &as(const TType<T> &type) const { 
      return any_cast<const typename T::Value &>(value); 
    }
    
    E call(VM &vm, Stack &stack, int arity, bool recursive, const Loc &loc) {
      return type.call(*this, vm, stack, arity, recursive, loc);
    }

    void dump(ostream &out) const {
      type.dump(*this, out);
    }

    E emit_call(VM &vm, 
		Env &env, 
		const Forms &args,
		const Loc &loc) const {
      return type.emit_call(*this, vm, env, args, loc);
    }

    E emit_id(VM &vm, 
	      Env &env, 
	      Forms &args,
	      const Loc &loc) const {
      return type.emit_id(*this, vm, env, args, loc);
    }

    E emit_literal(VM &vm, 
		   Env &env, 
		   Forms &args,
		   const Loc &loc) const {
      return type.emit_literal(*this, vm, env, args, loc);
    }

    E emit_ref(VM &vm, 
	       Env &env, 
	       Forms &args,
	       const Loc &loc) const {
      return type.emit_ref(*this, vm, env, args, loc);
    }

    bool is_true() const { 
      return type.is_true(*this); 
    }

    Cell iter() const {
      return type.iter(*this);
    }

    E js(ostream &out, const Loc &loc) const {
      return type.js(*this, out, loc);
    }

    void push(const Cell &item) {
      type.push(*this, item);
    }

    void say(ostream &out) const {
      type.say(*this, out);
    }
  };

  const Cell &NIL();

  const Cell &T();  
  const Cell &F();
  
  inline bool operator==(const Cell &left, const Cell &right) {
    if (left.type != right.type) {
      return false;
    }

    return left.type.eq(left, right);
  }

  inline strong_ordering operator<=>(const Cell &left, const Cell &right) {
    if (left.type == right.type) {
      return left.type.compare(left, right);
    }

    return left.type <=> right.type;
  }

  inline ostream &operator<<(ostream &out, const Cell &cell) {
    cell.dump(out);
    return out;
  }
}

#endif
